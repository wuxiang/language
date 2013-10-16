import org.apache.hadoop.net
import org.apache.hadoop.io

public class CatAllFileInHDFS
{
	public static void main(String[] args) throw Exception
	{
		InputStream in = null;
		try {
			in = new StandardSocketFactory().createSocket(args[0], args[1]).getInputStream();
			IOUtils.copyBytes(in, System.out, 4096, false);
		} finally {
			IOUtils.closeStream(in);
		}
	}
};
