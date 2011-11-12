public class GreeterApp
{
	private Keyboardread reader;
	public GreeterApp()
	{
		reader = new Keyboardread();
	}
	public void run()
	{
		String name = "";
		reader.prompt("please enter your name:");
		name = reader.getKeyBoardInput();
		reader.display(greet(name) + "\n");
	}
	public String greet(String name)
	{
		return "Hi " + name + " nice to meet you";
	}

	public static void main(String agrs[])
	{
		GreeterApp app = new GreeterApp();
		app.run();
	}
}
