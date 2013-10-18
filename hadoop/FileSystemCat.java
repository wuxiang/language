import org.apache.hadoop.conf;
import org.apache.hadoop.fs;

public class FileSystemCat
{
	public static void main(String[] args) throw Exception
	{
		String uri = args[0];
		Configuration conf = new Configuration();
		FileSystem  fs = FileSystem.get(URI.create(uri), conf);
		InputStream in = null;
		try {
			in = fs.open(new Path(uri));
			IOUtils.copyBytes(in, System.out, 4096, false);
			in.seek(0);
			IOUtils.copyBytes(in, System.out, 4096, false);
		} finally {
			IOUtils.closeStream(in);
		}
	}
}
