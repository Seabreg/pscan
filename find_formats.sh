#!/bin/sh
######################################################################
# Copyright (C) 2000,2007 Alan DeKok <aland@deployingradius.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
# USA
######################################################################
#
#  This is a quick & dirty shell script which roots through the
#  given files looking for function prototypes using variable
#  arguments, and a 'char' string, which we assume to be a format.
#
#  There's no guarantee that this will catch ALL of the problem
#  functions, (e.g. multi-line prototypes will be missed), but it
#  will catch the most common ones.
#
#  You'll have to turn the output into pscan rules by hand.
#
######################################################################
grep -n '\.\.\.' $@ | grep ';' | grep 'char'
