/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:57:50 by jlange            #+#    #+#             */
/*   Updated: 2017/11/16 14:50:20 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/ft_perror.h"

void	fill_error_one(char **tab)
{
	tab[0] = ft_strdup("Operation not permitted");
	tab[1] = ft_strdup("No such file or directory");
	tab[2] = ft_strdup("No such process");
	tab[3] = ft_strdup("Interrupted function call");
	tab[4] = ft_useless_norme();
	tab[5] = ft_strdup("No such device or address");
	tab[6] = ft_strdup("Arg list too long");
	tab[7] = ft_strdup("Exec format error");
	tab[8] = ft_strdup("Bad file descriptor");
	tab[9] = ft_strdup("No child processes");
	tab[10] = ft_strdup("Resource deadlock avoided");
	tab[11] = ft_strdup("Cannot allocate memory");
	tab[12] = ft_strdup("Permission denied");
	tab[13] = ft_strdup("Bad address");
	tab[14] = ft_strdup("Not a block device");
	tab[15] = ft_strdup("Resource busy");
	tab[16] = ft_strdup("File exists");
	tab[17] = ft_strdup("Improper link");
	tab[18] = ft_strdup("Operation not supported by device");
	tab[19] = ft_strdup("Not a directory");
	tab[20] = ft_strdup("Is a directory");
	tab[21] = ft_strdup("Invalid argument");
	tab[22] = ft_strdup("Too many open files in system");
	tab[23] = ft_strdup("Too many open files");
	tab[24] = ft_strdup("Inappropriate ioctl for device");
}

void	fill_error_two(char **tab)
{
	tab[0] = ft_strdup("Text file busy");
	tab[1] = ft_strdup("File too large");
	tab[2] = ft_strdup("Device out of space");
	tab[3] = ft_strdup("Illegal seek");
	tab[4] = ft_strdup("Read-only file system");
	tab[5] = ft_strdup("Too many links");
	tab[6] = ft_strdup("Broken pipe");
	tab[7] = ft_strdup("Numerical argument out of domain");
	tab[8] = ft_strdup("Numerical result out of range");
	tab[9] = ft_strdup("Resource temporarily unavailable");
	tab[10] = ft_strdup("Operation now in progress");
	tab[11] = ft_strdup("Operation already in progress");
	tab[12] = ft_strdup("Socket operation on non-socket");
	tab[13] = ft_strdup("Destination address required");
	tab[14] = ft_strdup("Message too long");
	tab[15] = ft_strdup("Protocol wrong type for socket");
	tab[16] = ft_strdup("Protocol not available");
	tab[17] = ft_strdup("Protocol not supported");
	tab[18] = ft_strdup("Socket type not supported");
	tab[19] = ft_strdup("Not supported");
	tab[20] = ft_strdup("Protocol family not supported");
	tab[21] = ft_strdup("Address family not supported by protocol family");
	tab[22] = ft_strdup("Address already in use");
	tab[23] = ft_strdup("Cannot assign requested address");
	tab[24] = ft_strdup("Network is down");
}

void	fill_error_three(char **tab)
{
	tab[0] = ft_strdup("Network is unreachable");
	tab[1] = ft_strdup("Network dropped connection on reset");
	tab[2] = ft_strdup("Software caused connection abort");
	tab[3] = ft_strdup("Connection reset by peer");
	tab[4] = ft_strdup("No buffer space available");
	tab[5] = ft_strdup("Socket is already connected");
	tab[6] = ft_strdup("Socket is not connected");
	tab[7] = ft_strdup("Cannot send after socket shutdown");
	tab[8] = ft_strdup("Undefined Error");
	tab[9] = ft_strdup("Operation timed out");
	tab[10] = ft_strdup("Connection refused");
	tab[11] = ft_strdup("Too many levels of symbolic links");
	tab[12] = ft_strdup("File name too long");
	tab[13] = ft_strdup("Host is down");
	tab[14] = ft_strdup("No route to host");
	tab[15] = ft_strdup("Directory not empty");
	tab[16] = ft_strdup("Too many processes");
	tab[17] = ft_strdup("Too many users");
	tab[18] = ft_strdup("Disc quota exceeded");
	tab[19] = ft_strdup("Stale NFS file handle");
	tab[20] = ft_strdup("RPC struct is bad");
	tab[21] = ft_strdup("Undefined error");
	tab[22] = ft_strdup("RPC version wrong");
	tab[23] = ft_strdup("RPC prog. not avail");
	tab[24] = ft_strdup("Program version wrong");
}

void	fill_error_four(char **tab)
{
	tab[0] = ft_strdup("Bad procedure for program");
	tab[1] = ft_strdup("No locks available");
	tab[2] = ft_strdup("Function not implemented");
	tab[3] = ft_strdup("Inappropriate file type or format");
	tab[4] = ft_strdup("Authentication error");
	tab[5] = ft_strdup("Need authenticator");
	tab[6] = ft_strdup("Device power is off");
	tab[7] = ft_strdup("Device error");
	tab[8] = ft_strdup("Value too large to be stored in data type");
	tab[9] = ft_strdup("Bad executable (or shared library)");
	tab[10] = ft_strdup("Bad CPU type in executable");
	tab[11] = ft_strdup("Shared library version mismatch");
	tab[12] = ft_strdup("Malformed Mach-o file");
	tab[13] = ft_strdup("Operation canceled");
	tab[14] = ft_strdup("Identifier removed");
	tab[15] = ft_strdup("No message of desired type");
	tab[16] = ft_strdup("Illegal byte sequence");
	tab[17] = ft_strdup("Attribute not found");
	tab[18] = ft_strdup("Bad message");
	tab[19] = ft_strdup("Reserved");
	tab[20] = ft_strdup("No message available");
	tab[21] = ft_strdup("Reserved");
	tab[22] = ft_strdup("No STREAM resources");
	tab[23] = ft_strdup("Not a STREAM");
	tab[24] = ft_strdup("Protocol error");
}

void	fill_error_five(char **tab)
{
	tab[0] = ft_strdup("STREAM ioctl() timeout");
	tab[1] = ft_strdup("Operation not supported on socket");
}
