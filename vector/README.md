# vector

this library is a fast library for neural networks or other task, which change a lot of values at the same time.
in this documentation the most functions won't be explained because they are obvios.

## Todo

correct error in free memory causing double free

## License

[![AGPL-3.0 License](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl.html)

Libraries
Copyright (C) 2019 Calvin Reu

SPDX-License-Identifier: AGPL-3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/).


## [variables](vector.hpp#L10)

#### memory
memory is a allocator to get memory.

#### m_size
m_size is the ammount of objects in the vector.

#### m_max_size
m_max_size is the amount of allocated memory.

## member functions

### [constructor](vector.hpp#L92)
allocate memory note: m_size won't change 

### [operator+/-](vector.hpp#L99)
adds / subtracks all values from one tho another vector

### [get_vectorValue](vector.hpp#L108)
returns the sum off all values in the vector.

### [add_memory](vector.hpp#L111)
get more memory note: m_size won't change.

### [iterator::operator&](vector.hpp#L73)
returns pointer to the data

### all allocation functions
throws std::bad_alloc if there is not enought memory for more information look [here](https://en.cppreference.com/w/cpp/memory/allocator)

## short overwiew

### vector functions
| function name   | return value | arguments    | line | purpose                                                                                |
|-----------------|--------------|--------------|------|----------------------------------------------------------------------------------------|
| vector          | void         |              | 91   | initialize with 0                                                                      |
| vector          | void         | size_t       | 92   | allocate size_t memory                                                                 |
| ~vector()       | void         |              | 93   | destruct objects and deallocate memory                                                 |
| vector()        | void         | vector &&    | 94   | copy pointer and size and set other size to 0                                          |
| vector()        | void         | vector       | 95   | copy_construct data from other vector to this vector                                   |
| operator[]      | T&/const T&  | size_t       | 97   | return data pointer [size_t]                                                           |
| operator+/-     | vector       | vector       | 99   | add/subtract every value from the vectors and return a vector with results             |
| operator+=/-=   | void         | vector       | 101  | add/subtract every values from the vectors and use the results to recreate this vector |
| operator=       | void         | vector       | 103  | copy all values to this vector                                                         |
| operator=       | void         | vector &&    | 104  | copy pointern and size                                                                 |
| size            | const size_t |              | 106  | return own size                                                                        |
| max_size        | const size_t |              | 107  | return allocated memory                                                                |
| get_vectorValue | T            |              | 108  | add all values in the vector and return the result                                     |
| get_ValPtr      | T*/const T*  |              | 109  | returns pointer  to data                                                               |
| add_memory      | void         | size_t       | 111  | allocates extra size_t memory                                                          |
| assign          | void         | size_t, args | 113  | construct size_t objects with args                                                     |
| push            | void         | args         | 115  | construct 1 object with args                                                           |
| free            | void         | size_t       | 116  | destruct the last size_t elements in the vector                                        |
| begin           | iterator     |              | 118  | return iterator, which points to the vector begin                                      |
| end             | iterator     |              | 119  | return iterator, which points to the vector end+1;                                     |
| rbegin          | iterator     |              | 120  | return iterator, which points at the last element                                      |
| rend            | iterator     |              | 121  | return iterator, which points one elemt before the vector starts                       |

### iterator functions
| function name           | return value | arguments | line  | purpose                                         |
|-------------------------|--------------|-----------|-------|-------------------------------------------------|
| iterator                | void         | T*        | 60    | init iterator with T                            |
| operator</>/<=/>=/==/!= | bool         | iterator  | 62-67 | check variable position difference left < right |
| operator*               | T&/const T&  |           | 69    | get variable iterator points to                 |
| operator->              | T&/ constT&  |           | 71    | get variable iterator points to                 |
| operator&               | T*           |           | 73    | get the pointer in the iterator                 |
| operator++/--           | void         |           | 76    | increase/decrease pointer by 1                  |
| operator+=/-=           | void         | size_t    | 79    | add/ subtract size_t from pointer               |
| operator+/-             | iterator     | size_t    | 84    | return result of pointer+/-size_t               |
| operator=               | void         | size_t    | 82    | pointer = other pointer                         |


### private functions
| function name | return value | arguments         | line  | purpose                               |
|---------------|--------------|-------------------|-------|---------------------------------------|
| destruct      | void         | size_t            | 15-24 | destruct objects at vector end        |
| move          | void         | T*                | 26-35 | move all objects to T                 |
| construct     | void         | agrs, T*          | 37-43 | construct a object at T               |
| copy          | void         | T* 1,T* 2, size_t | 45-54 | copy from 1 to 2 the amount of size_t |
