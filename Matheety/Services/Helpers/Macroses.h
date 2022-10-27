
#pragma once

#define Getter(Name,Property,Type) \
const Type Get##Name()\
{return Property;}\

