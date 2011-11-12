import java.io.*;

public class Keyboardread
{
	private BufferedReader reader;
	public  Keyboardread()
	{
		reader = new BufferedReader( new InputStreamReader(System.in));
	}
	private String readKeyBoard()
	{
		String line = "";
		try
		{
			line = reader.readLine();
		} catch(IOException e)
		{
			e.printStackTrace();
		}
		return line;
	}

	public String getKeyBoardInput()
	{
		return readKeyBoard();
	}

	public int getKeyBoardInteger()
	{
		return Integer.parseInt(readKeyBoard());
	}
	public double getKeyBoardDouble()
	{
		return Double.parseDouble(readKeyBoard());
	}
	public void prompt(String s)
	{
		System.out.print(s);
	}
	public void display(String s)
	{
		System.out.print(s);
	}
}

