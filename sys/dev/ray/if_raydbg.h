/*
 * Copyright (C) 2000
 * Dr. Duncan McLennan Barclay, dmlb@ragnet.demon.co.uk.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY DUNCAN BARCLAY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL DUNCAN BARCLAY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: if_ray.c,v 1.17 2000/04/04 06:43:30 dmlb Exp $
 *
 */

/*
 * Debugging odds and odds
 */

/*
 * RAY_DEBUG settings
 *
 *	RECERR		Recoverable error's
 *	SUBR		Subroutine entry
 *	BOOTPARAM	Startup CM dump
 *	STARTJOIN	State transitions for start/join
 *	CCS		CCS info
 *	IOCTL		IOCTL calls
 *	MBUF		MBUFs dumped
 *	RX		packet types reported
 *	CM		common memory re-mapping
 *	COM		new command sleep/wakeup
 */
#define RAY_DBG_RECERR		0x0001
#define RAY_DBG_SUBR		0x0002
#define RAY_DBG_BOOTPARAM	0x0004
#define RAY_DBG_STARTJOIN	0x0008
#define RAY_DBG_CCS		0x0010
#define RAY_DBG_IOCTL		0x0020
#define RAY_DBG_MBUF		0x0080
#define RAY_DBG_RX		0x0100
#define RAY_DBG_CM		0x0200
#define RAY_DBG_COM		0x0400
/* Cut and paste this into a kernel configuration file */
#if 0
#define RAY_DEBUG	(				\
 			/* RAY_DBG_RECERR	| */	\
 			/* RAY_DBG_SUBR		| */ 	\
			/* RAY_DBG_BOOTPARAM	| */	\
			/* RAY_DBG_STARTJOIN	| */	\
			/* RAY_DBG_CCS		| */	\
                        /* RAY_DBG_IOCTL	| */	\
                        /* RAY_DBG_MBUF		| */ 	\
                        /* RAY_DBG_RX		| */	\
                        /* RAY_DBG_CM		| */	\
                        /* RAY_DBG_COM		| */	\
			0				\
			)
#endif

#if RAY_DEBUG

/* XXX This macro assumes that common memory is mapped into kernel space and
 * XXX does not indirect through SRAM macros - it should */
#define RAY_DHEX8(p, l, mask) do { if (RAY_DEBUG & mask) {	\
    u_int8_t *i;						\
    for (i = p; i < (u_int8_t *)(p+l); i += 8)			\
    	printf("  0x%08lx %8D\n",				\
		(unsigned long)i, (unsigned char *)i, " ");	\
} } while (0)

#define RAY_DPRINTF(sc, mask, fmt, args...) do {if (RAY_DEBUG & (mask)) {\
    printf("ray%d: %s(%d) " fmt "\n",					\
    	(sc)->unit, __FUNCTION__ , __LINE__ , ##args);			\
} } while (0)

#else
#define RAY_DHEX8(p, l, mask)
#define RAY_DPRINTF(sc, mask, fmt, args...)
#endif /* RAY_DEBUG > 0 */

/*
 * These override macros defined in if_ray.c to turn them into
 * debugging ones.
 */
#if RAY_DEBUG & RAY_DBG_COM
#define RAY_COM_DUMP(sc, com, s) do { if (RAY_DEBUG & RAY_DBG_COM) {	\
    printf("ray%d: %s(%d) %s com entry 0x%p\n",				\
        (sc)->unit, __FUNCTION__ , __LINE__ , (s) , (com));		\
    printf("  c_mesg %s\n", (com)->c_mesg);				\
    printf("  c_flags 0x%b\n", (com)->c_flags, RAY_COM_FLAGS_PRINTFB);	\
    printf("  c_retval 0x%x\n", (com)->c_retval);			\
    printf("  c_ccs 0x%0x index 0x%02x\n",				\
        com->c_ccs, RAY_CCS_INDEX((com)->c_ccs));			\
} } while (0)

#define RAY_COM_CHECK(sc, com) do { if (RAY_DEBUG & RAY_DBG_COM) {	\
    ray_com_ecf_check((sc), (com), __FUNCTION__ );			\
} } while (0)

#define RAY_COM_MALLOC(function, flags)	\
	ray_com_malloc((function), (flags), __STRING(function));
#endif /* RAY_DEBUG & RAY_DBG_COM */

#if RAY_DEBUG & RAY_DBG_MBUF
#define RAY_MBUF_DUMP(sc, m, s)	ray_dump_mbuf((sc), (m), (s))
#endif /* RAY_DEBUG & RAY_DBG_MBUF */
