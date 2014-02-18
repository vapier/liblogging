/* The stdlog systemd journal driver
 *
 * Copyright (C) 2014 Adiscon GmbH
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
 *
 * THIS SOFTWARE IS PROVIDED BY ADISCON AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL ADISCON OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <systemd/sd-journal.h>
#include "stdlog-intern.h"
#include "stdlog.h"

/* dummy just needed for driver interface */
static void
jrnl_open(stdlog_channel_t __attribute__((unused)) ch)
{
}
/* dummy just needed for driver interface */
static void
jrnl_close(stdlog_channel_t __attribute__((unused)) ch)
{
}

static void
jrnl_log(stdlog_channel_t ch, const int severity)
{
	// TODO: error handling!!!
	sd_journal_send("MESSAGE=%s", ch->msgbuf,
                "PRIORITY=%d", severity,
                NULL);
}

void
__stdlog_set_jrnl_drvr(stdlog_channel_t ch)
{
	ch->drvr.open = jrnl_open;
	ch->drvr.close = jrnl_close;
	ch->drvr.log = jrnl_log;
}