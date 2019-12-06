/*
 * DIO.c
 *		AVR Digital Input Output, self-written library
 *  Created on: Aug 26, 2017
 *      Author: Asmer Amen
 */
#include "DIO.h"
#include"utilss.h"

/*
 *  States the Direction of the PIN: INPUT/OUTPUT
 */
extern void DIO_voidSetPinDirection(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalDirection)
{
	if((DIO_u8LocalPinToSet>=0 && DIO_u8LocalPinToSet<=31) && (DIO_u8DIOLocalDirection==0 || DIO_u8DIOLocalDirection==1))
	{
		if( (DIO_u8LocalPinToSet / 8) == 0)
		{
			assign_bit(DDRA, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 1)
		{
			assign_bit(DDRB, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 2)
		{
			assign_bit(DDRC, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 3)
		{
			assign_bit(DDRD, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
	} /* end if */
} /*end function */

/*
 *  States the Value of the PIN: HIGH/LOW
 */
extern void DIO_voidWritePin(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalValue)
{
	if((DIO_u8LocalPinToSet>=0 && DIO_u8LocalPinToSet<=31) && (DIO_u8DIOLocalValue==0 || DIO_u8DIOLocalValue==1))
	{
		if( (DIO_u8LocalPinToSet / 8) == 0)
		{
			assign_bit(PORTA, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 1)
		{
			assign_bit(PORTB, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 2)
		{
			assign_bit(PORTC, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 3)
		{
			assign_bit(PORTD, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalValue);
		}
	}/* end if */
}/* end function */


/*
 *  Reads the Value of the PIN: HIGH/LOW
 */
extern U8 DIO_u8ReadPin(U8 DIO_u8LocalPintToRead)
{
	U8 DIO_u8DataToBeRead;
	if((DIO_u8LocalPintToRead>=0) && (DIO_u8LocalPintToRead<=31))
	{
		if( (DIO_u8LocalPintToRead/8) == 0)
		{
			DIO_u8DataToBeRead = get_bit(PINA,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 1)
		{
			DIO_u8DataToBeRead = get_bit(PINB,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 2)
		{
			DIO_u8DataToBeRead = get_bit(PINC,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 3)
		{
			DIO_u8DataToBeRead = get_bit(PIND,(DIO_u8LocalPintToRead%8) );
		}
	}
	return DIO_u8DataToBeRead;
} /*end function */


/*
 *  States the Direction of the Port: INPUT/OUTPUT
 */
extern void DIO_voidSetPortDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOLocalDirection)
{
	/* declare Port A as Output */
	if(DIO_u8LocalPortToSet == 'A')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
		DDRA = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
		DDRA = 0x00;
		}
	}

	/* declare Port A as Output */
	if(DIO_u8LocalPortToSet == 'A')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRA = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRA = 0x00;
		}
	} /* end Port A assigning */

	/* declare Port B as Output */
	if(DIO_u8LocalPortToSet == 'B')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRB = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRB = 0x00;
		}
	}/* end Port B assigning */

	/* declare Port C as Output */
	if(DIO_u8LocalPortToSet == 'C')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRC = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRC = 0x00;
		}
	} /* end Port C assigning */

	/* declare Port D as Output */
	if(DIO_u8LocalPortToSet == 'D')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRD = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRD = 0x00;
		}
	}/* end Port C assigning */
} /* end DIO_voidSetPortDirection Function */


/*
 *  States the Value of the Port: HIGH/LOW
 */
extern void DIO_voidWritePort(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet)
{
	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'A')
	{
			PORTA = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'B')
	{
		PORTB = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'C')
	{
		PORTC = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'D')
	{
		PORTD = DIO_u8ValueToSet;
	}
}/* end DIO_voidWritePort Function */


#if 0
/*
 *  Reads the Value of the PIN: HIGH/LOW
 */
extern U8 DIO_u8ReadPOrt(U8 DIO_u8LocalPortToRead)
{
	U8 DIO_u8DataToBeRead;

	if( DIO_u8LocalPortToRead == 'A')
	{
		DIO_u8DataToBeRead = get_bit(PINA,(DIO_u8LocalPorttToRead%8) );
	}
	else if(DIO_u8LocalPortToRead == 'B')
	{
		DIO_u8DataToBeRead = get_bit(PINB,(DIO_u8LocalPorttToRead%8) );
	}
	else if(DIO_u8LocalPortToRead == 'C')
	{
		DIO_u8DataToBeRead = get_bit(PINC,(DIO_u8LocalPorttToRead%8) );
	}
	else if(DIO_u8LocalPortToRead == 'D')
	{
		DIO_u8DataToBeRead = get_bit(PIND,(DIO_u8LocalPorttToRead%8) );
	}

	return DIO_u8DataToBeRead;
} /*end DIO_u8ReadPOrt function */
#endif
