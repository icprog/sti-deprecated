/*! \file MixedValue.cpp
 *  \author Jason Michael Hogan
 *  \brief Source-file for the class MixedValue
 *  \section license License
 *
 *  Copyright (C) 2009 Jason Hogan <hogan@stanford.edu>\n
 *  This file is part of the Stanford Timing Interface (STI).
 *
 *  The STI is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The STI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the STI.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <MixedValue.h>
#include <sstream>
#include <utils.h>

MixedValue::MixedValue()
{
	type = Empty;
}
MixedValue::MixedValue(const MixedValue& copy)
{
	setValue(copy);
}

MixedValue::~MixedValue()
{
}



bool MixedValue::operator==(const MixedValue& other) const
{
	if(type != other.getType())
		return false;

	bool result;

	switch(type)
	{
	case Boolean:
		result = ( value_b == other.getBoolean() );
		break;
	case Int:
		result = ( value_i == other.getInt() );
		break;
	case Double:
		result = ( value_d == other.getDouble() );
		break;
	case String:
		result = ( value_s.compare(other.getString()) == 0 );
		break;
	case Vector:
		{
			const MixedValueVector& otherValues = other.getVector();

			if(values.size() != otherValues.size())
			{
				result = false;
			}
			else
			{
				result = true;

				for(unsigned i = 0; (i < otherValues.size() && i < values.size()); i++)
				{
					result &= ( values.at(i) == otherValues.at(i) );
				}
			}
		}
		break;
	case Empty:
		return true;	//both are empty
	default:
		//this should never happen
		result = false;
		break;
	}

	return result;
}

bool MixedValue::operator!=(const MixedValue& other) const
{
	return !( (*this) == other );
}

void MixedValue::setValue(bool value)
{
	clear();

	value_b = value;
	type = Boolean;
}

void MixedValue::setValue(int value)
{
	clear();

	value_i = value;
	type = Int;
}


void MixedValue::setValue(double value)
{
	clear();

	value_d = value;
	type = Double;
}

void MixedValue::setValue(std::string value)
{
	clear();

	value_s = value;
	type = String;
}

void MixedValue::setValue(const MixedValue& value)
{
	//clear();
	//type = value.getType();

	switch( value.getType() )
	{
	case Boolean:
		setValue( value.getBoolean() );
		break;
	case Int:
		setValue( value.getInt() );
		break;
	case Double:
		setValue( value.getDouble() );
		break;
	case String:
		setValue( value.getString() );
		break;
	case Vector:
		setValue( value.getVector() );
		//{
		//	const MixedValueVector& newValues = value.getVector();
		//
		//	for(unsigned i = 0; i < newValues.size(); i++)
		//	{
		//		addValue( newValues.at(i) );
		//	}
		//}
		break;
	case Empty:
		setValue();
		break;
	default:
		//this should never happen
		break;
	}

}

void MixedValue::setValue(const STI::Types::TValMixed& value)
{
	switch( value._d() )
	{
	case STI::Types::ValueNumber:
		setValue( value.number() );
		break;
	case STI::Types::ValueString:
		setValue( std::string( value.stringVal() ) );
		break;
	case STI::Types::ValueVector:
		setValue( value.vector() );
		break;
	case STI::Types::ValueNone:
		setValue();
		break;
	default:
		//this should never happen
		break;
	}
}

void MixedValue::setValue(const STI::Types::TValMixedSeq& value)
{
	clear();
	type = Vector;

	for(unsigned i = 0; i < value.length(); i++)
	{
		addValue( value[i] );
	}
}
void MixedValue::setValue()
{
	clear();
	type = Empty;
}

void MixedValue::clear()
{
	values.clear();
	type = Vector;
}

MixedValue::MixedValueType MixedValue::getType() const
{
	return type;
}
bool MixedValue::getBoolean() const
{
	if(type == Boolean)
		return value_b;
	else
		return (getNumber() != 0);
}

int MixedValue::getInt() const
{
	if(type == Int)
		return value_i;
	else
		return static_cast<int>( getNumber() );
}

double MixedValue::getDouble() const
{
	if(type == Double)
		return value_d;
	else
		return static_cast<double>( getNumber() );
}

double MixedValue::getNumber() const
{
	double result;
	
	switch(type)
	{
	case Boolean:
		return ( static_cast<double>(value_b) );
	case Int:
		return ( static_cast<double>(value_i) );
	case Double:
		return value_d;
	case String:
		if(STI::Utils::stringToValue(value_s, result))
			return result;
		else
		{
			result = 0;
			return (0.0 / result);	//NaN
		}
	default:
		result = 0;
		return (0.0 / result);	//NaN
	}
}

std::string MixedValue::getString() const
{
	return value_s;
}

const MixedValueVector& MixedValue::getVector() const
{
	return values;
}

const STI::Types::TValMixed MixedValue::getTValMixed() const
{
	STI::Types::TValMixed value;
	
	switch(type)
	{
	case Boolean:
		value.number( static_cast<double>(value_b) );
		break;
	case Int:
		value.number( static_cast<double>(value_i) );
		break;
	case Double:
		value.number( value_d );
		break;
	case String:
		value.stringVal( value_s.c_str() );
		break;
	case Vector:
		value.vector(STI::Types::TValMixedSeq());
		value.vector().length( values.size() );
		for(unsigned i = 0; i < values.size(); i++)
		{
			value.vector()[i] = values.at(i).getTValMixed();
		}
		break;
	case Empty:
		value.emptyValue(true);		//ValueNone
		break;
	}

	return value;
}

void MixedValue::convertToVector()
{
	if(type == Vector)
		return;

	MixedValueType oldType = type;

	clear();
	type = Vector;

	switch(oldType)
	{
	case Boolean:
		addValue(value_b);
		break;
	case Int:
		addValue(value_i);
		break;
	case Double:
		addValue(value_d);
		break;
	case String:
		addValue(value_s);
		break;
	case Empty:
		break;
	default:
		//this should never happen
		break;
	}
}

std::string MixedValue::print() const
{
	std::stringstream result;
	
	switch(type)
	{
	case Boolean:
		result << value_b;
		break;
	case Int:
		result << value_i;
		break;
	case Double:
		result << value_d;
		break;
	case String:
		result << value_s;
		break;
	case Vector:
		result << "(";
		for(unsigned i = 0; i < values.size(); i++)
		{
			if(i > 0)
			{
				result << ",";
			}
			result << values.at(i).print();
		}
		result << ")";
		break;
	case Empty:
		result << "<Empty>";
		break;
	default:
		//this should never happen
		break;
	}

	return result.str();
}

