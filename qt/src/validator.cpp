/***************************************************************************
 *   Copyright (C) 2009 by Alex Montgomery and Nedko Arnaudov   *
 *   check@Adaon   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "validator.h"

QValidator::State Validator::validate ( QString & input, int & pos ) const
{
   Q_UNUSED(pos);
   
   for (int i = 0; i < input.length(); i++)
   {
      if (input[i] < '0' || input[i] > '9')
         return QValidator::Invalid;
   }
   
   return QValidator::Acceptable;
}

QValidator::State HexValidator::validate ( QString & input, int & pos ) const
{
   Q_UNUSED(pos);
   
   for (int i = 0; i < input.length(); i++)
   {
      if ( (input[i] < '0' || input[i] > '9') && (input[i] < 'a' || input[i] > 'f') && (input[i] < 'A' || input[i] > 'F'))
         return QValidator::Invalid;
   }
   
   return QValidator::Acceptable;
}
