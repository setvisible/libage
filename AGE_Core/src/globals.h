/* - AGE Core Library - Copyright (C) 2018 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AGE_GLOBAL_H
#define AGE_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#    define MY_DECL_EXPORT     __declspec(dllexport)
#    define MY_DECL_IMPORT     __declspec(dllimport)
#  else
#    define MY_DECL_EXPORT     __attribute__((visibility("default")))
#    define MY_DECL_IMPORT     __attribute__((visibility("default")))
#    define MY_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif


#if defined(LIBAGE_LIBRARY)
#  define LIBAGESHARED_EXPORT MY_DECL_EXPORT
#else
#  define LIBAGESHARED_EXPORT MY_DECL_IMPORT
#endif

#ifdef __cplusplus
}
#endif

#define LIBAGE_BEGIN_NAMESPACE  namespace AGE {
#define LIBAGE_END_NAMESPACE    }

#endif // AGE_GLOBAL_H
