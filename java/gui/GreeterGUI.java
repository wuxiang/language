import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GreeterGUI extends JFrame implements ActionListener
{
	private JTextArea     display;
	private JTextField    inField;
	private JButton       goButton;
	private GreeterApp       greeter;

	public GreeterGUI(String title)
	{
		greeter = new GreeterApp();
		buildGUI();
		setTitle(title);
		pack();
		setVisible(true);
	}

	private void buildGUI()
	{
		//every should be insert into a main frame's container
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		display = new JTextArea(10, 30);
		inField = new JTextField(10);
		goButton = new JButton("click here for a greeting!");
		goButton.addActionListener(this);
		JPanel inputpanel = new JPanel();
		inputpanel.add(new JLabel("Input your name here: "));
		inputpanel.add(inField);
		inputpanel.add(goButton);

		contentPane.add("Center", display);
		contentPane.add("South", inputpanel);
	}

	public void actionPerformed(ActionEvent e)
	{
		if (e.getSource() == goButton)
		{
			String name = inField.getText();
			display.append(greeter.greet(name) + "\n");
		}
	}

	public static void main(String args[])
	{
		new GreeterGUI("Greeter");
	}
}
