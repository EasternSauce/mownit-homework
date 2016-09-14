import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;
import javax.swing.JComponent;
import java.io.*;

public class CountView extends JFrame{
	private JLabel introLabel = new JLabel("Select a method");
	private ImageIcon image;
	private JLabel imageLabel = new JLabel();
	private JLabel approxLabel = new JLabel("Current iteration: , Approximation: ");
	private JButton iterButton = new JButton("Next iter");
	private String [] methods = {"choose one", "Brent", "bisection", "Newton"};
	private JComboBox<String> methodCombo = new JComboBox<String>(methods);
	private JButton lsButton = new JButton("Draw least squares");



	CountView(){
		this.setTitle("One dimensional root finding");
		this.setSize(640, 720);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel countPanel = new JPanel(new GridBagLayout());


		GridBagConstraints gc = new GridBagConstraints();

		gc.weightx = 1;
		gc.weighty = 1;

		gc.gridx = 0;
		gc.gridy = 0;
		gc.gridwidth = 2;
		countPanel.add(introLabel, gc);

		gc.gridx = 0;
		gc.gridy = 1;
		gc.gridwidth = 2;
		countPanel.add(methodCombo, gc);


		gc.gridx = 0;
		gc.gridy = 2;
		gc.gridwidth = 1;
		countPanel.add(approxLabel, gc);

		gc.gridx = 1;
		gc.gridy = 2;
		gc.gridwidth = 1;
		countPanel.add(iterButton, gc);

		gc.gridx = 1;
		gc.gridy = 3;
		gc.gridwidth = 1;
		countPanel.add(lsButton, gc);


		gc.gridx = 0;
		gc.gridy = 5;
		gc.gridwidth = 3;
		countPanel.add(imageLabel, gc);

		this.add(countPanel);

	}

	public void setImage(String imagePath){
		try{
		ImageIcon image = new ImageIcon(ImageIO.read(new File(imagePath)));
		imageLabel.setIcon(image);
		}catch(Exception e){}

	}

	public void addIterListener(final MyButtonListener listener){
		iterButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(MyButtonListener.canPressIter){
					MyButtonListener.canPressIter = false;
					new SwingWorker<Integer, Integer>(){
						public Integer doInBackground(){
							listener.workerJob();
							return 0;
						}

						public void done(){
							listener.done();
							MyButtonListener.canPressIter = true;
						}
					}.execute();
				}
			}
		});
	}

	public void addComboListener(final MyButtonListener listener){
		methodCombo.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent e){
				new SwingWorker<Integer, Integer>(){
					public Integer doInBackground(){
						JComboBox cb = (JComboBox)e.getSource();
						String method = (String)cb.getSelectedItem();
						listener.choice = method;
						listener.workerJob();
						return 0;
					}

					public void done(){
						listener.done();
					}
				}.execute();
			}
		});

	}

	public void addLsListener(final MyButtonListener listener){
		lsButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(MyButtonListener.canPressLs){
					MyButtonListener.canPressLs = false;
					new SwingWorker<Integer, Integer>(){
						public Integer doInBackground(){
							listener.workerJob();
							return 0;
						}

						public void done(){
							listener.done();
							MyButtonListener.canPressLs = true;
						}
					}.execute();
				}
			}
		});
	}


	
	public void setLabel(int iter, double root){
		approxLabel.setText("Current iteration: " + iter + ", Approximation: " + root);
	}

	public void setIntro(String text){
		introLabel.setText(text);

	}
}

