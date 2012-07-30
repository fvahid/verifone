
#include "uclfactory.h"		//Includes Ucl library 
#include "verixtimer.h"		//Includes Timer
#include "appobj.h"		//Includes Application Object


short SetParamLandLine(short paramId, unsigned char *buffer, short size)
{
    if(buffer == NULL)
	return UCL_FAILURE;
    if(size == 0)
	return UCL_FAILURE;
    switch (paramId)
    {
    case ESCAPE_GUARD_TIME:
	escapeGuardTime = atoi((char*)buffer);
	break;
	
    case BAUDRATE:
	baudRate = buffer[0];
	break;
    case FORMAT:
	format = buffer[0];
	break;
	
    case PROTOCOL:
	protocol = buffer[0];
	break;
    case PARAMETER:
	parameter = buffer[0];
	break;
    case SDLC_PARM_OPTION:
	sdlcparmoption = buffer[0];
	break;
    case SDLC_PARM_ADDRESS: 
	sdlcparmaddress = buffer[0];
	break;
	
    case MDM_TYPE:
	mdmType = buffer[0];
	break;
    case DIAL_TYPE:
	dialType = buffer[0];
	break;
    case PHONE_NUMBER:
	memcpy(phoneNo, buffer,size);
	return size;
    case INIT_STRING:
	memcpy(initString, buffer,size);
	return size;
    case HANGUP_STRING:
	memcpy(hangUpString, buffer,size);
	return size;
    case STARTUP_STRING:
	memcpy(startUpString, buffer,size);
	return size;
    case MODEL_NO:
	memcpy(modelNo, buffer,size);
	return size;
    default:
	
	return UCL_FAILURE;
    }
    return UCL_SUCCESS;
}


extern OS_RETURN_VALS SDK_RS232Open( RS232MODE Mode, RS232DATA *pData ) {

    UclFactory *ptrFactory  = CreateUclFactory();
    Ucl *ptrUcl;
    short  retVal;
    // Using timer struct provided by library
    CommTimer *timer = (CommTimer*)CreateVerixCommTimer();  
    
    // Using ApplicationObj struct provided by application
    // AppObj *llAppObj = CreateAppObj(0); // for landline  
    AppObj *gsmAppObj = CreateAppObj(1); // for Gsm			

    // create the Object on COM3
    ptrUcl = uclFactory->Create(COM3, &retVal, gsmAppObj, RS232);     //  for RS232

    //Timeout period for Open in milliseconds
    timer->SetTimer(2000);	
    return retVal = ptrUcl->Open(ptrUcl, timer);
}


extern OS_RETURN_VALS SDK_RS232Close( void ) {
    Ucl *ptrUcl;
    CommTimer *Timer = (CommTimer*)CreateVerixCommTimer();
    
    //Timeout period for Close in milliseconds
    timer->SetTimer(2000);		
    return OS_RETURN_VALS = ptrUcl->Close(ptrUcl,timer);
}


extern OS_RETURN_VALS SDK_RS232Reset( void ) {
    
}

extern OS_RETURN_VALS SDK_RS232Info( RS232INFO Type ) {

    // timeout for get status
    timer->SetTimer(3000);
    
// Returns device status i.e. OPENED,CLOSED etc..
    retVal = ptrUcl->GetStatus(ptrUcl,DEVICE_STATUS, timer);	
    
//Returns Port Status i.e. INPUT_PENDING, OUTPUT_PENDING etc..
    retVal = ptrUcl->GetStatus(ptrUcl,PORT_STATUS, timer);		
    
//Returns dock status i.e. STATUS_DOCKED or STATUS_UNDOCKED..
    retVal = ptrUcl->GetStatus(ptrUcl,DOCK_STATUS, timer);	
    
//Returns line status i.e. E_UCL_NO_LINE or UCL_SUCCESS or E_UCL_FEATURE_NOT_SUPPORTED..
    retVal = ptrUcl->GetStatus(ptrUcl,LINE_STATUS, timer);		

    
}



extern OS_RETURN_VALS SDK_RS232Write( UBYTE *pBuffer,
				      UWORD BufLen,
				      OS_TIMES Timeout,
				      IOSTATUS *pStatus ) {
    Ucl *ptrUcl;
    CommTimer *Timer = (CommTimer*)CreateVerixCommTimer();
    
    sBytes = 0;
    //Timeout period for receive in milliseconds
    timer->SetTimer(Timeout);	
    return OS_RETURN_VALS = ptrUcl->Send(ptrUcl,pBuffer,BufLen,sBytes,timer);

}


extern OS_RETURN_VALS SDK_RS232Read( UBYTE *pBuffer,
				     UWORD *pBufLen,
				     OS_TIMES Timeout,
				     IOSTATUS *pStatus ) {
    Ucl *ptrUcl;
    CommTimer *Timer = (CommTimer*)CreateVerixCommTimer();
    
    rBytes = 0;
    //Timeout period for receive in milliseconds
    timer->SetTimer(Timeout);
    return OS_RETURN_VALS = ptrUcl->Receive(ptrUcl,pBuffer,pBufLen,rBytes,timer);
}






