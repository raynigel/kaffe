/*
 * Java core library component.
 *
 * Copyright (c) 1997, 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file.
 */

/**
 * @author Edouard Parmelan <Edouard.Parmelan@France.NCR.COM>
 */
package java.util;

import java.lang.String;
import java.lang.System;

final public class BitSet
    implements Cloneable, java.io.Serializable
{
    /**
     * The bits in this BitSet.
     * @serial The ith bit is stored in bits[i/64] (aka bits[i>>6])
     * at bit position (i%64) (aka i & 0x3F).
     */
    private long bits[];


    /**
     * return the offset in bits[].
     */
    private static int bitOffset(int bit) {
	return bit >> 6;
    }

    /**
     * return the mask of the bit in bits[bitOffset(bit)].
     */
    private static long bitMask(int bit) {
	return 1L << (bit & 0x3F);
    }

    /**
     * ensure bits can hold nr bit.
     */
    private void ensureSize(int nr) {
	int len = bitOffset(nr + 0x3F);
	if (len > bits.length) {
	    long b[] = new long[len];
	    System.arraycopy(bits, 0, b, 0, bits.length);
	    bits = b;
	}
    }


    /**
     * Create a new BitSet.
     */
    public BitSet() {
	this(64);
    }


    /**
     * Create a new BitSet that can hold nr bits.
     * All bits are initialized to false.
     *
     * @param nr the inital size of the set.
     */
    public BitSet(int nr) {
	if (nr < 0)
	    throw new NegativeArraySizeException();
	bits = new long[bitOffset(nr + 0x3F)];
    }


    /**
     * Set a bit in the set.
     * @param bit the bit to set.
     */
    public synchronized void set(int bit) {
	if (bit < 0)
	    throw new IndexOutOfBoundsException();
	ensureSize(bit+1);
	bits[bitOffset(bit)] |= bitMask(bit);
    }

    /**
     * Clear a bit in the set.
     * @param bit the bit to clear.
     */
    public synchronized void clear(int bit) {
	if (bit < 0)
	    throw new IndexOutOfBoundsException();
	ensureSize(bit+1);
	bits[bitOffset(bit)] &= ~bitMask(bit);
    }

    /**
     * Returns the value of the bit in the set.
     * @param bit the bit to check.
     * @return the value of the bit.
     */
    public synchronized boolean get(int bit) {
	if (bit < 0)
	    throw new IndexOutOfBoundsException();
	int k = bitOffset(bit);
	if (k < bits.length)
	    return ((bits[k] & bitMask(bit)) != 0);
	else
	    return false;
    }


    /**
     * Returns the index of the highest set bit in the set plus one.
     *
     * @return the logical size of this set.
     * @since JDK1.2
     */
    public synchronized int length() {
	long b[] = bits;
	int n = b.length - 1;
	while ((n >= 0) && (b[n] == 0L))
	    n--;
	if (n < 0)
	    return 0;

	long m = b[n];
	long k = 1L << 63;
	n = (n + 1) << 6;

	// k never 0 because m != 0
	while ((m & k) == 0L) {
	    n--;
	    k >>= 1;
	}
	return n;
    }


    /**
     * @return the number of bits in the set.
     */
    public int size() {
	// don't need synchronization
	return bits.length << 6;
    }


    /**
     * Compares this object againts the specified object.
     * The result is true if and only if the argument is not null and is
     * a BitSet object that has exactly the same set of bits set to true.
     * The current sizes of the two sets are not compared.
     * @return true if the objects are the same; false otherwise.
     */
    public boolean equals(Object obj) {
	if (obj == this)
	    return true;
	if ((obj == null) || !(obj instanceof BitSet))
	    return false;

	Object lock1, lock2;
	if (System.identityHashCode(this) < System.identityHashCode(obj)) {
	    lock1 = this;
	    lock2 = obj;
	}
	else {
	    lock1 = obj;
	    lock2 = this;
	}
	synchronized(lock1) {
	    synchronized(lock2) {
		long a[] = bits;
		long b[] = ((BitSet)obj).bits;

		// Check commun bits
		int nr = Math.min(a.length, b.length);
		for (int i = nr; i-- > 0; ) {
		    if (a[i] != b[i])
			return false;
		}

		// Check upper bits
		if (nr != b.length)
		    a = b;
		else if (nr == a.length)
		    return true;
		for(int i = a.length; i-- > nr; ) {
		    if (a[i] != 0L)
			return false;
		}
		return true;
	    }
	}
    }


    /**
     * Performs a logical AND of this set and the argument bit set.
     * Result of the mathematical intersection of two sets.
     * @param set a bit set.
     */
    public void and(BitSet bitset) {
	if (this == bitset)
	    return;
	Object lock1, lock2;
	if (System.identityHashCode(this) < System.identityHashCode(bitset)) {
	    lock1 = this;
	    lock2 = bitset;
	}
	else {
	    lock1 = bitset;
	    lock2 = this;
	}
	synchronized(lock1) {
	    synchronized(lock2) {
		// a = a and b
		long a[] = bits;
		long b[] = bitset.bits;

		int nr = Math.min(a.length, b.length);
		for (int i = nr; i-- > 0; )
		    a[i] &= b[i];
		// clear upper bits
		for (int i = a.length; i-- > nr; )
		    a[i] = 0;
	    }
	}
    }


    /**
     * Performs a logical AND of this set and the COMPLEMENT of the argument
     * bit set.
     * Result of the mathematical substaction of two set.
     * @param set a bit set.
     * @since JDK1.2
     */
    public void andNot(BitSet bitset) {
	if(this == bitset) {
	    synchronized(this) {
		long a[] = bits;
		for (int i = a.length; i-- > 0; )
		    a[i] = 0;
	    }
	    return;
	}
	Object lock1, lock2;
	if (System.identityHashCode(this) < System.identityHashCode(bitset)) {
	    lock1 = this;
	    lock2 = bitset;
	}
	else {
	    lock1 = bitset;
	    lock2 = this;
	}
	synchronized(lock1) {
	    synchronized(lock2) {
		// a = a and (not b)
		long a[] = bits;
		long b[] = bitset.bits;

		int nr = Math.min(a.length, b.length);
		for (int i = nr; i-- > 0; )
		    a[i] &= ~b[i];
		// don't nead to check upper bits
	    }
	}
    }


    /**
     * Performs a logical OR of this set and the argument bit set.
     * Result of the mathematical union of two sets.
     * @param set a bit set.
     */
    public void or(BitSet bitset) {
	if (this == bitset)
	    return;
	Object lock1, lock2;
	if (System.identityHashCode(this) < System.identityHashCode(bitset)) {
	    lock1 = this;
	    lock2 = bitset;
	}
	else {
	    lock1 = bitset;
	    lock2 = this;
	}
	synchronized(lock1) {
	    synchronized(lock2) {
		// a = a or b
		long a[] = bits;
		long b[] = bitset.bits;

		int nr = Math.min(a.length, b.length);
		for (int i = nr; i-- > 0; )
		    a[i] |= b[i];
		// Set upper bits
		if (a.length < b.length) {
		    // grow only for set bits
		    ensureSize(bitset.length());
		    a = bits;
		    for (int i = bits.length; i-- > nr; )
			a[i] = b[i];
		}
	    }
	}
    }


    /**
     * Performs a logical EXCLUSIVE OR of this set and the argument bit set.
     *
     * @param set a bit set.
     */
    public void xor(BitSet bitset) {
	if(this == bitset) {
	    synchronized(this) {
		long a[] = bits;
		for (int i = a.length; i-- > 0; )
		    a[i] = 0;
	    }
	    return;
	}
	Object lock1, lock2;
	if (System.identityHashCode(this) < System.identityHashCode(bitset)) {
	    lock1 = this;
	    lock2 = bitset;
	}
	else {
	    lock1 = bitset;
	    lock2 = this;
	}
	synchronized(lock1) {
	    synchronized(lock2) {
		// a = a xor b
		long a[] = bits;
		long b[] = bitset.bits;

		int nr = Math.min(a.length, b.length);
		for (int i = nr; i-- > 0; )
		    a[i] ^= b[i];
		// Set upper bits,  X ^ 0 == 0 ^ X == X
		if (a.length < b.length) {
		    // grow only for set bits
		    ensureSize(bitset.length());
		    a = bits;
		    for (int i = bits.length; i-- > nr; )
			a[i] = b[i];
		}
	    }
	}
    }


    /**
     * Returns a hash code value for this bit set.
     */
    public synchronized int hashCode() {
	long h = 1234L;
	for (int i = bits.length; --i >= 0; ) {
	    h ^= bits[i] * (i + 1);
	}
	return (int)((h >> 32) ^ h);
    }


    /**
     * Cloning this BitSet produces a new BitSet that is equal to it.
     * The clone of the bit set is another bit set that has exactly the same
     * bits set to true as this bit set and the same current size.
     */
    public synchronized Object clone() {
	BitSet bitset;
	try {
	    bitset = (BitSet)super.clone();
	}
	catch (CloneNotSupportedException _) {
	    return null;
	}
	bitset.bits = new long[bits.length];
	// if clone could reduce the size: copy up to last set bit
	// bitset.bits = new long[bitOffset(length() + 0x3F)];
	System.arraycopy(bits, 0, bitset.bits, 0, bitset.bits.length);
	return bitset;
    }


    /**
     * Returns a string representation of this bit set.
     * For every index for which this BitSet contains a bit in the set state,
     * the decimal representation of that index is included in the result.
     * Such indeces are listed in order from lowest to highest, separated by
     * ",&nbsp;" (a comma and a space) and surrounded by braces, resulting in
     * the usual mathematical notation for a set of integers.
     */
    public synchronized String toString() {
	int bit;
	int nbits = length();
	boolean first = true;
	StringBuffer sb = new StringBuffer();
	sb.append('{');
	for (bit = 0; bit < nbits; bit++) {
	    if (get(bit)) {
		if (!first)
		    sb.append(", ");
		else
		    first = false;
		sb.append(bit);
	    }
	}
	sb.append('}');
	return sb.toString();
    }
}
