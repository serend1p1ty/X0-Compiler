#pragma once
#include "global.h"

/* object stored in data stack */
class StackObject
{

private:

	DataType ResultType (DataType dt1, DataType dt2)
	{
		if (dt1 == Double || dt2 == Double)
		{
			return Double;
		}
		else if (dt1 == Char || dt2 == Char)
		{
			return Char;
		}
		else
		{
			return Int;
		}
	}

public:

	DataType dataType;
	int intData;         /* store int/char/bool data */
	double dblData;      /* store double data */

	StackObject ()
	{
		dataType = Nul;
	}

	void assign (StackObject s)
	{
		if (dataType != Double)
		{
			if (s.dataType != Double)
			{
				intData = s.intData;
			}
			else
			{
				intData = (int)s.dblData;
			}
		}
		else
		{
			if (s.dataType != Double)
			{
				dblData = s.intData;
			}
			else
			{
				dblData = s.dblData;
			}
		}
	}

	/*StackObject operator = (const StackObject& s)
	{
		dataType = s.dataType;
		intData = s.intData;
		dblData = s.dblData;
		return *this;
	}*/

	StackObject operator + (const StackObject& s)
	{
		StackObject res;
		if (dataType != Double && s.dataType != Double)
		{
			res.intData = intData + s.intData;
		}
		else
		{
			res.dblData = (dataType != Double ? intData : dblData)
				+ (s.dataType != Double ? s.intData : s.dblData);
		}
		res.dataType = ResultType (dataType, s.dataType);
		return res;
	}

	StackObject operator - (const StackObject& s)
	{
		StackObject res;
		if (dataType != Double && s.dataType != Double)
		{
			res.intData = intData - s.intData;
		}
		else
		{
			res.dblData = (dataType != Double ? intData : dblData)
				- (s.dataType != Double ? s.intData : s.dblData);
		}
		res.dataType = ResultType (dataType, s.dataType);
		return res;
	}

	StackObject operator - ()
	{
		intData = -intData;
		dblData = -dblData;
		return *this;
	}

	StackObject operator * (const StackObject& s)
	{
		StackObject res;
		if (dataType != Double && s.dataType != Double)
		{
			res.intData = intData * s.intData;
		}
		else
		{
			res.dblData = (dataType != Double ? intData : dblData)
				* (s.dataType != Double ? s.intData : s.dblData);
		}
		res.dataType = ResultType (dataType, s.dataType);
		return res;
	}

	StackObject operator / (const StackObject& s)
	{
		StackObject res;
		if (dataType != Double && s.dataType != Double)
		{
			res.intData = intData / s.intData;
		}
		else
		{
			res.dblData = (dataType != Double ? intData : dblData)
				/ (s.dataType != Double ? s.intData : s.dblData);
		}
		res.dataType = ResultType (dataType, s.dataType);
		return res;
	}

	StackObject operator % (const StackObject& s)
	{
		/* The operand of mod operation must be integer */
		if (dataType == Double || s.dataType == Double)
		{
			ErrorHandler (39);
		}
		StackObject res;
		res.intData = intData % s.intData;
		res.dataType = Int;
		return res;
	}

	StackObject operator == (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			== (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator != (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			!= (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator > (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			> (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator >= (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			>= (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator < (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			< (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator <= (const StackObject& s)
	{
		StackObject res;
		res.dataType = Bool;
		res.intData = (dataType != Double ? intData : dblData)
			<= (s.dataType != Double ? s.intData : s.dblData);
		return res;
	}

	StackObject operator && (const StackObject& s)
	{
		/* The operand of && must be integer */
		if (dataType == Double || s.dataType == Double)
		{
			ErrorHandler (41);
		}
		StackObject res;
		res.intData = intData && s.intData;
		res.dataType = Bool;
		return res;
	}

	StackObject operator || (const StackObject& s)
	{
		/* The operand of || must be integer */
		if (dataType == Double || s.dataType == Double)
		{
			ErrorHandler (42);
		}
		StackObject res;
		res.intData = intData || s.intData;
		res.dataType = Bool;
		return res;
	}

	StackObject operator ^ (const StackObject& s)
	{
		/* The operand of xor must be integer */
		if (dataType == Double || s.dataType == Double)
		{
			ErrorHandler (44);
		}
		StackObject res;
		res.intData = intData ^ s.intData;
		res.dataType = Bool;
		return res;
	}

	StackObject operator ! ()
	{
		/* The operand of ! must be integer */
		if (dataType == Double)
		{
			ErrorHandler (43);
		}
		StackObject res;
		res.intData = !intData;
		res.dataType = Bool;
		return res;
	}
};
