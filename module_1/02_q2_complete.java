public class Le {

    // Read the four bytes begining at p and assemble them little-endian
    public static int load_int_little(byte[] p) 
	{
		int a = p[0];
		int b = p[1];
		int c = p[2];
		int d = p[3];
		
		return (d << 24) | (c << 16) | (b << 8) | a;
    }

}