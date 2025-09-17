/* This is a comment. */
INT MAIN f()
BEGIN
   REAL r;
   READ(r, "Please input a real number as the radius of a circle:");
   REAL z := 2 * 3.14 * r;
   WRITE(z, "The circumference of the circle is");
   WRITE(3.14 * r * r, "The circumference of the circle is");
END

