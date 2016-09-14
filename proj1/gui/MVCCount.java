

public class MVCCount{
	public static void main(String args[]){
		CountView theView = new CountView();
		CountModel theModel = new CountModel();
		CountController theController = new CountController(theView, theModel);
		theView.setVisible(true);
	}

}
