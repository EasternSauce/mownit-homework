import java.io.*;
import java.util.*;

public class CountController{
	private final CountView theView;
	private final CountModel theModel;
	private int iter = 0;

	public CountController(CountView view, CountModel model){
		this.theView = view;
		this.theModel = model;

		ArrayList<Integer> iters = new ArrayList<Integer>();
		ArrayList<Double> roots = new ArrayList<Double>();


	
		theView.addIterListener(new MyButtonListener(){
			public void workerJob(){
				try{
				PrintWriter writer = new PrintWriter("root.txt", "UTF-8");
				writer.println("root");
				writer.println("" + roots.get(iter));
				writer.close();
				}catch(Exception e){}

				theView.setLabel(iters.get(iter), roots.get(iter));

				String cmd = "Rscript ../plot.r";
				Runtime run = Runtime.getRuntime();
				try{
				Process pr = run.exec(cmd);
				pr.waitFor();
				}catch(Exception e){}
			}

			public void done(){
				System.out.println("let go of iter");
				theView.setImage("plot.jpg");
				iter++;
			}

		});
		

		theView.addLsListener(new MyButtonListener(){
			public void workerJob(){
				String cmd = "./../least_squares";
				Runtime run = Runtime.getRuntime();
				try{
					Process pr = run.exec(cmd);
					pr.waitFor();
				}catch(Exception e){}


				cmd = "Rscript ../plot_ls.r";
				run = Runtime.getRuntime();
				try{
					Process pr = run.exec(cmd);
					pr.waitFor();
				}catch(Exception e){}

			}

			public void done(){
				System.out.println("let go of ls");
				theView.setImage("plot_ls.jpg");
			}

		});


		theView.addComboListener(new MyButtonListener(){
			public void workerJob(){
				iter = 0;
				iters.clear();
				roots.clear();

				if(choice.equals("Brent")){
					String cmd = "./../main";
					Runtime run = Runtime.getRuntime();
					try{
					Process pr = run.exec(cmd);
					pr.waitFor();
					}catch(Exception e){}

				}
				if(choice.equals("bisection")){
					String cmd = "./../main2";
					Runtime run = Runtime.getRuntime();
					try{
					Process pr = run.exec(cmd);
					pr.waitFor();
					}catch(Exception e){}

				}

				if(choice.equals("Newton")){
					String cmd = "./../main3";
					Runtime run = Runtime.getRuntime();
					try{
					Process pr = run.exec(cmd);
					pr.waitFor();
					}catch(Exception e){}

				}


				String csvFile = "output.txt";
				BufferedReader br = null;
				String line = "";
				String cvsSplitBy = ",";

				
				try {

					br = new BufferedReader(new FileReader(csvFile));
					line = br.readLine();
					while ((line = br.readLine()) != null) {

						String[] parts = line.split(cvsSplitBy);
						iters.add(Integer.parseInt(parts[0]));
						roots.add(Double.parseDouble(parts[1]));

					}
				} catch(Exception e){e.printStackTrace();}

			}

			public void done(){
				theView.setIntro("Method: " + choice);

			}


			
		});


	}
}
