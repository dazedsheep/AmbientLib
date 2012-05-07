#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _DEBUG
#define DBG_MSG_W(msg,caption) MessageBox(NULL,msg,caption, MB_OK)
#else
#define DBG_MSG_W(msg,caption)
#endif

#endif