/*     
 * java.lang.reflect.Array.c
 *
 * Copyright (c) 1996, 1997
 *	Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include "config.h"
#include "config-std.h"
#include "config-mem.h"
#include "../../../kaffe/kaffevm/object.h"
#include "../../../kaffe/kaffevm/classMethod.h"
#include "../../../kaffe/kaffevm/baseClasses.h"
#include "../../../kaffe/kaffevm/itypes.h"
#include "../../../kaffe/kaffevm/soft.h"
#include "java_lang_reflect_Array.h"
#include "java_lang_Boolean.h"
#include "java_lang_Byte.h"
#include "java_lang_Character.h"
#include "java_lang_Short.h"
#include "java_lang_Integer.h"
#include "java_lang_Long.h"
#include "java_lang_Float.h"
#include "java_lang_Double.h"
#include <native.h>
#include "defs.h"

jint
java_lang_reflect_Array_getLength(struct Hjava_lang_Object* obj)
{
	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	return (obj_length((HArrayOfObject*)obj));
}

struct Hjava_lang_Object*
java_lang_reflect_Array_get(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangIntegerClass,"(I)V",
						(jint)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangShortClass,"(S)V",
						(jint)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangLongClass,"(J)V",
						(jlong)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangByteClass,"(B)V",
						(jint)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_booleanClass ) {
		HArrayOfBoolean *arr = (HArrayOfBoolean *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangBooleanClass,"(Z)V",
						(jint)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangCharacterClass,"(C)V",
						(jint)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangFloatClass,"(F)V",
						(jfloat)(unhand_array(arr)->body[elem]));
	}
	else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return execute_java_constructor(0,javaLangDoubleClass,"(D)V",
						(jdouble)(unhand_array(arr)->body[elem]));
	}
	else {
		/* If clazz isn't one of the above then it's either a
		 * reference or unresolved (and so a reference).
		 */

		HArrayOfObject *arr = (HArrayOfObject *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	}
}

jbool
java_lang_reflect_Array_getBoolean(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_booleanClass ) {
		HArrayOfBoolean *arr = (HArrayOfBoolean *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jbyte
java_lang_reflect_Array_getByte(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jchar
java_lang_reflect_Array_getChar(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jshort
java_lang_reflect_Array_getShort(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jint
java_lang_reflect_Array_getInt(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jlong
java_lang_reflect_Array_getLong(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jfloat
java_lang_reflect_Array_getFloat(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

jdouble
java_lang_reflect_Array_getDouble(struct Hjava_lang_Object* obj, jint elem)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		return unhand_array(arr)->body[elem];
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_set(struct Hjava_lang_Object* obj, jint elem, struct Hjava_lang_Object* val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	if (!CLASS_IS_PRIMITIVE(CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj)))) {
		HArrayOfObject *arr = (HArrayOfObject *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		if (val == NULL || soft_instanceof(CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj)), val)) {
			unhand_array(arr)->body[elem] = val;
		} else {
			SignalError("java.lang.IllegalArgumentException", "");
		}
		return;
	}

	clazz = OBJECT_CLASS(val);
	
	if ( clazz == javaLangIntegerClass ) {
		java_lang_reflect_Array_setInt(obj, elem, unhand(((Hjava_lang_Integer *)val))->value );
	}
	else if ( clazz == javaLangBooleanClass ) {
		java_lang_reflect_Array_setBoolean(obj, elem, unhand(((Hjava_lang_Boolean *)val))->value );
	}
	else if ( clazz == javaLangByteClass ) {
		java_lang_reflect_Array_setByte(obj, elem, unhand(((Hjava_lang_Byte *)val))->value );
	}
	else if ( clazz == javaLangShortClass ) {
		java_lang_reflect_Array_setShort(obj, elem, unhand(((Hjava_lang_Short *)val))->value );
	}
	else if ( clazz == javaLangCharacterClass ) {
		java_lang_reflect_Array_setChar(obj, elem, unhand(((Hjava_lang_Character *)val))->value );
	}
	else if ( clazz == javaLangLongClass ) {
		java_lang_reflect_Array_setLong(obj, elem, unhand(((Hjava_lang_Long *)val))->value );
	}
	else if ( clazz == javaLangFloatClass ) {
		java_lang_reflect_Array_setFloat(obj, elem, unhand(((Hjava_lang_Float *)val))->value );
	}
	else if ( clazz == javaLangDoubleClass ) {
		java_lang_reflect_Array_setDouble(obj, elem, unhand(((Hjava_lang_Double *)val))->value );
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
      	}
}

void
java_lang_reflect_Array_setBoolean(struct Hjava_lang_Object* obj, jint elem, jbool val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_booleanClass ) {
		HArrayOfBoolean *arr = (HArrayOfBoolean *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setByte(struct Hjava_lang_Object* obj, jint elem, jbyte val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_byteClass ) {
		HArrayOfByte *arr = (HArrayOfByte *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setChar(struct Hjava_lang_Object* obj, jint elem, jchar val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_charClass ) {
		HArrayOfChar *arr = (HArrayOfChar *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setShort(struct Hjava_lang_Object* obj, jint elem, jshort val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_shortClass ) {
		HArrayOfShort *arr = (HArrayOfShort *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setInt(struct Hjava_lang_Object* obj, jint elem, jint val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_intClass ) {
		HArrayOfInt *arr = (HArrayOfInt *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setLong(struct Hjava_lang_Object* obj, jint elem, jlong val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_longClass ) {
		HArrayOfLong *arr = (HArrayOfLong *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setFloat(struct Hjava_lang_Object* obj, jint elem, jfloat val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_floatClass ) {
		HArrayOfFloat *arr = (HArrayOfFloat *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

void
java_lang_reflect_Array_setDouble(struct Hjava_lang_Object* obj, jint elem, jdouble val)
{
	Hjava_lang_Class *clazz;

	if (!CLASS_IS_ARRAY(OBJECT_CLASS(obj)))
		SignalError("java.lang.IllegalArgumentException", "");

	clazz = CLASS_ELEMENT_TYPE(OBJECT_CLASS(obj));
	
	if ( clazz == _Jv_doubleClass ) {
		HArrayOfDouble *arr = (HArrayOfDouble *)obj;
		if (elem < 0 || elem >= obj_length(arr))
			SignalError("java.lang.ArrayIndexOutOfBoundsException", "");
		
		unhand_array(arr)->body[elem] = val;
	} else {
		SignalError("java.lang.IllegalArgumentException", "");
	}
}

struct Hjava_lang_Object*
java_lang_reflect_Array_newArray(struct Hjava_lang_Class* clazz, jint size)
{
	if (size < 0) {
		SignalError("java.lang.NegativeArraySizeException", "");
	} else {
		return (newArray(clazz, size));
	}
}

struct Hjava_lang_Object*
java_lang_reflect_Array_multiNewArray(struct Hjava_lang_Class* clazz, HArrayOfInt* sizes)
{
	int* dims;
	int i;
	int s;
	Hjava_lang_Object* array;

	s = obj_length(sizes);

	if (s == 0) {
		SignalError("java.lang.IllegalArgumentException", "zero dimensions");
	}

	dims = KCALLOC(s+1, sizeof(int));

	/* Copy dimentions into array */
	for( i = 0; i < s; i++ ) {
		dims[i] = unhand_array(sizes)->body[i];
		if (dims[i] < 0) {
			SignalError("java.lang.NegativeArraySizeException", "");
		}
		clazz = lookupArray(clazz);
	}
	dims[i] = -1;

	/* Create multi-dimension array */
	array = newMultiArray(clazz, dims);
	KFREE(dims);

	return (array);
}
