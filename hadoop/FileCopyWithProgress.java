import org.apache.hadoop.conf;
import org.apache.hadoop.fs;
import org.apache.hadoop.util;

public class FileCopyWithProgress
{
	public static  void main(String args[])
	{
		String localSrc = args[0];
		String dst = args[1];
		InputStream in = new BufferedInputStream(new FileInputStream(localSrc));

		Configuration conf = new Configuration();
		FileSystem fs = FileSystem.get(URI.create(dst), conf);
		OutputStream out = fs.create(new Path(dst), new Progressable() {
			public void progress() {
				System.out.print(".");
			}
		});

		IOUtils.copyBytes(in, out, 4096, true);
	}
}
