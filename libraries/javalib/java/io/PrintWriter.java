/*
 * Java core library component.
 *
 * Copyright (c) 1997, 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file.
 */

package java.io;


public class PrintWriter extends Writer {

  private static final String newline = System.getProperty("line.separator");

  protected Writer out;
  private boolean flsh;
  private boolean error;

  public PrintWriter(Writer out)
  {
    this(out, false);
  }

  public PrintWriter(Writer out, boolean autoFlush)
  {
    this.out = out;
    flsh = autoFlush;
    error = false;
  }

  public PrintWriter(OutputStream out)
  {
    this(out, false);
  }

  public PrintWriter(OutputStream out, boolean autoFlush)
  {
    this.out = new OutputStreamWriter(out);
    flsh = autoFlush;
    error = false;
  }

  public void flush()
  {
    try {
      out.flush();
    }
    catch (IOException _) {
      error = true;
    }
  }

  public void close()
  {
    try {
      out.close();
    }
    catch (IOException _) {
      error = true;
    }
  }

  public boolean checkError()
  {
    flush();
    return (error);
  }

  protected void setError()
  {
    error = true;
  }

  public void write(int c)
  {
    char ch[] = new char[1];
    ch[0] = (char)c;
    write(ch, 0, 1);
  }

  public void write(char buf[], int off, int len)
  {
    try {
      out.write(buf, off, len);
    }
    catch (IOException _) {
      error = true;
    }
  }

  public void write(char buf[])
  {
    write(buf, 0, buf.length);
  }

  public void write(String s, int off, int len)
  {
    if (s == null) {
      write(String.valueOf(s));
    }
    else {
      write(s.toCharArray(), off, len);
    }
  }

  public void write(String s)
  {
    if (s == null) {
      write(String.valueOf(s));
    }
    else {
      write(s.toCharArray(), 0, s.length());
    }
  }

  public void print(boolean b)
  {
    write(b ? "true" : "false");
  }

  public void print(char c)
  {
    write((int)c);
  }

  public void print(int i)
  {
    write(Integer.toString(i));
  }

  public void print(long l)
  {
    write(Long.toString(l));
  }

  public void print(float f)
  {
    write(Float.toString(f));
  }

  public void print(double d)
  {
    write(Double.toString(d));
  }

  public void print(char s[])
  {
    write(s, 0, s.length);
  }

  public void print(String s)
  {
    write(s);
  }

  public void print(Object obj)
  {
    print(String.valueOf(obj));
  }

  public void println()
  {
    write(newline);
    if (flsh) {
      flush();
    }
  }

  public void println(boolean x)
  {
    println(x ? "true" : "false");
  }

  public void println(char x)
  {
    synchronized(lock) {
      write((int)x);
      println();
    }
  }

  public void println(int x)
  {
    println(Integer.toString(x));
  }

  public void println(long x)
  {
    println(Long.toString(x));
  }

  public void println(float x)
  {
    println(Float.toString(x));
  }

  public void println(double x)
  {
    println(Double.toString(x));
  }

  public void println(char x[])
  {
    synchronized(lock) {
      write(x, 0, x.length);
      println();
    }
  }

  public void println(String x)
  {
    synchronized(lock) {
      write(x);
      println();
    }
  }

  public void println(Object x)
  {
    println(String.valueOf(x));
  }

}
