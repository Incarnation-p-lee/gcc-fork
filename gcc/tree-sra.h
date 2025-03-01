/* Scalar Replacement of Aggregates (SRA) converts some structure
   references into scalar references, exposing them to the scalar
   optimizers.
   Copyright (C) 2019-2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

bool type_internals_preclude_sra_p (tree type, const char **msg);
unsigned HOST_WIDE_INT sra_get_max_scalarization_size (void);
bool sra_total_scalarization_would_copy_same_data_p (tree t1, tree t2);


/* Return true iff TYPE is stdarg va_list type (which early SRA and IPA-SRA
   should leave alone).  */

inline bool
is_va_list_type (tree type)
{
  return TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (va_list_type_node);
}
