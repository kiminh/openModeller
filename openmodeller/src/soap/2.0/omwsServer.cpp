/* omwsServer.cpp
   Generated by gSOAP 2.8.15 from omws_api.hh

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "omwsH.h"

namespace omws {

SOAP_SOURCE_STAMP("@(#) omwsServer.cpp ver 2.8.15 2013-08-03 00:37:13 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if (omws::soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:ping"))
		return soap_serve_omws__ping(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getAlgorithms"))
		return soap_serve_omws__getAlgorithms(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getLayers"))
		return soap_serve_omws__getLayers(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:createModel"))
		return soap_serve_omws__createModel(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getModel"))
		return soap_serve_omws__getModel(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:testModel"))
		return soap_serve_omws__testModel(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getTestResult"))
		return soap_serve_omws__getTestResult(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:projectModel"))
		return soap_serve_omws__projectModel(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getProgress"))
		return soap_serve_omws__getProgress(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getLog"))
		return soap_serve_omws__getLog(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getLayerAsUrl"))
		return soap_serve_omws__getLayerAsUrl(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getProjectionMetadata"))
		return soap_serve_omws__getProjectionMetadata(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:evaluateModel"))
		return soap_serve_omws__evaluateModel(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getModelEvaluation"))
		return soap_serve_omws__getModelEvaluation(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:samplePoints"))
		return soap_serve_omws__samplePoints(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getSamplingResult"))
		return soap_serve_omws__getSamplingResult(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:runExperiment"))
		return soap_serve_omws__runExperiment(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:getResults"))
		return soap_serve_omws__getResults(soap);
	if (!soap_match_tag(soap, soap->tag, "omws:cancel"))
		return soap_serve_omws__cancel(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__ping(struct soap *soap)
{	struct omws__ping soap_tmp_omws__ping;
	struct omws__pingResponse soap_tmp_omws__pingResponse;
	soap_default_omws__pingResponse(soap, &soap_tmp_omws__pingResponse);
	soap_default_omws__ping(soap, &soap_tmp_omws__ping);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__ping(soap, &soap_tmp_omws__ping, "omws:ping", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__ping(soap, soap_tmp_omws__ping._, soap_tmp_omws__pingResponse.status);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__pingResponse(soap, &soap_tmp_omws__pingResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__pingResponse(soap, &soap_tmp_omws__pingResponse, "omws:pingResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__pingResponse(soap, &soap_tmp_omws__pingResponse, "omws:pingResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getAlgorithms(struct soap *soap)
{	struct omws__getAlgorithms soap_tmp_omws__getAlgorithms;
	struct omws__getAlgorithmsResponse out;
	soap_default_omws__getAlgorithmsResponse(soap, &out);
	soap_default_omws__getAlgorithms(soap, &soap_tmp_omws__getAlgorithms);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getAlgorithms(soap, &soap_tmp_omws__getAlgorithms, "omws:getAlgorithms", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getAlgorithms(soap, soap_tmp_omws__getAlgorithms._, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getAlgorithmsResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getAlgorithmsResponse(soap, &out, "omws:getAlgorithmsResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getAlgorithmsResponse(soap, &out, "omws:getAlgorithmsResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getLayers(struct soap *soap)
{	struct omws__getLayers soap_tmp_omws__getLayers;
	struct omws__getLayersResponse out;
	soap_default_omws__getLayersResponse(soap, &out);
	soap_default_omws__getLayers(soap, &soap_tmp_omws__getLayers);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getLayers(soap, &soap_tmp_omws__getLayers, "omws:getLayers", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getLayers(soap, soap_tmp_omws__getLayers._, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getLayersResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getLayersResponse(soap, &out, "omws:getLayersResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getLayersResponse(soap, &out, "omws:getLayersResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__createModel(struct soap *soap)
{	struct omws__createModel soap_tmp_omws__createModel;
	struct omws__createModelResponse soap_tmp_omws__createModelResponse;
	soap_default_omws__createModelResponse(soap, &soap_tmp_omws__createModelResponse);
	soap_default_omws__createModel(soap, &soap_tmp_omws__createModel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__createModel(soap, &soap_tmp_omws__createModel, "omws:createModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__createModel(soap, soap_tmp_omws__createModel.om__ModelParameters, soap_tmp_omws__createModelResponse.ticket);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__createModelResponse(soap, &soap_tmp_omws__createModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__createModelResponse(soap, &soap_tmp_omws__createModelResponse, "omws:createModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__createModelResponse(soap, &soap_tmp_omws__createModelResponse, "omws:createModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getModel(struct soap *soap)
{	struct omws__getModel soap_tmp_omws__getModel;
	struct omws__getModelResponse out;
	soap_default_omws__getModelResponse(soap, &out);
	soap_default_omws__getModel(soap, &soap_tmp_omws__getModel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getModel(soap, &soap_tmp_omws__getModel, "omws:getModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getModel(soap, soap_tmp_omws__getModel.ticket, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getModelResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getModelResponse(soap, &out, "omws:getModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getModelResponse(soap, &out, "omws:getModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__testModel(struct soap *soap)
{	struct omws__testModel soap_tmp_omws__testModel;
	struct omws__testModelResponse soap_tmp_omws__testModelResponse;
	soap_default_omws__testModelResponse(soap, &soap_tmp_omws__testModelResponse);
	soap_default_omws__testModel(soap, &soap_tmp_omws__testModel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__testModel(soap, &soap_tmp_omws__testModel, "omws:testModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__testModel(soap, soap_tmp_omws__testModel.om__TestParameters, soap_tmp_omws__testModelResponse.ticket);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__testModelResponse(soap, &soap_tmp_omws__testModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__testModelResponse(soap, &soap_tmp_omws__testModelResponse, "omws:testModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__testModelResponse(soap, &soap_tmp_omws__testModelResponse, "omws:testModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getTestResult(struct soap *soap)
{	struct omws__getTestResult soap_tmp_omws__getTestResult;
	struct omws__testResponse out;
	soap_default_omws__testResponse(soap, &out);
	soap_default_omws__getTestResult(soap, &soap_tmp_omws__getTestResult);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getTestResult(soap, &soap_tmp_omws__getTestResult, "omws:getTestResult", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getTestResult(soap, soap_tmp_omws__getTestResult.ticket, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__testResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__testResponse(soap, &out, "omws:testResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__testResponse(soap, &out, "omws:testResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__projectModel(struct soap *soap)
{	struct omws__projectModel soap_tmp_omws__projectModel;
	struct omws__projectModelResponse soap_tmp_omws__projectModelResponse;
	soap_default_omws__projectModelResponse(soap, &soap_tmp_omws__projectModelResponse);
	soap_default_omws__projectModel(soap, &soap_tmp_omws__projectModel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__projectModel(soap, &soap_tmp_omws__projectModel, "omws:projectModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__projectModel(soap, soap_tmp_omws__projectModel.om__ProjectionParameters, soap_tmp_omws__projectModelResponse.ticket);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__projectModelResponse(soap, &soap_tmp_omws__projectModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__projectModelResponse(soap, &soap_tmp_omws__projectModelResponse, "omws:projectModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__projectModelResponse(soap, &soap_tmp_omws__projectModelResponse, "omws:projectModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getProgress(struct soap *soap)
{	struct omws__getProgress soap_tmp_omws__getProgress;
	struct omws__getProgressResponse soap_tmp_omws__getProgressResponse;
	soap_default_omws__getProgressResponse(soap, &soap_tmp_omws__getProgressResponse);
	soap_default_omws__getProgress(soap, &soap_tmp_omws__getProgress);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getProgress(soap, &soap_tmp_omws__getProgress, "omws:getProgress", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getProgress(soap, soap_tmp_omws__getProgress.tickets, soap_tmp_omws__getProgressResponse.progress);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getProgressResponse(soap, &soap_tmp_omws__getProgressResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getProgressResponse(soap, &soap_tmp_omws__getProgressResponse, "omws:getProgressResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getProgressResponse(soap, &soap_tmp_omws__getProgressResponse, "omws:getProgressResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getLog(struct soap *soap)
{	struct omws__getLog soap_tmp_omws__getLog;
	struct omws__getLogResponse soap_tmp_omws__getLogResponse;
	soap_default_omws__getLogResponse(soap, &soap_tmp_omws__getLogResponse);
	soap_default_omws__getLog(soap, &soap_tmp_omws__getLog);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getLog(soap, &soap_tmp_omws__getLog, "omws:getLog", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getLog(soap, soap_tmp_omws__getLog.ticket, soap_tmp_omws__getLogResponse.log);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getLogResponse(soap, &soap_tmp_omws__getLogResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getLogResponse(soap, &soap_tmp_omws__getLogResponse, "omws:getLogResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getLogResponse(soap, &soap_tmp_omws__getLogResponse, "omws:getLogResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getLayerAsUrl(struct soap *soap)
{	struct omws__getLayerAsUrl soap_tmp_omws__getLayerAsUrl;
	struct omws__getLayerAsUrlResponse soap_tmp_omws__getLayerAsUrlResponse;
	soap_default_omws__getLayerAsUrlResponse(soap, &soap_tmp_omws__getLayerAsUrlResponse);
	soap_default_omws__getLayerAsUrl(soap, &soap_tmp_omws__getLayerAsUrl);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getLayerAsUrl(soap, &soap_tmp_omws__getLayerAsUrl, "omws:getLayerAsUrl", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getLayerAsUrl(soap, soap_tmp_omws__getLayerAsUrl.id, soap_tmp_omws__getLayerAsUrlResponse.url);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getLayerAsUrlResponse(soap, &soap_tmp_omws__getLayerAsUrlResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getLayerAsUrlResponse(soap, &soap_tmp_omws__getLayerAsUrlResponse, "omws:getLayerAsUrlResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getLayerAsUrlResponse(soap, &soap_tmp_omws__getLayerAsUrlResponse, "omws:getLayerAsUrlResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getProjectionMetadata(struct soap *soap)
{	struct omws__getProjectionMetadata soap_tmp_omws__getProjectionMetadata;
	struct omws__getProjectionMetadataResponse out;
	soap_default_omws__getProjectionMetadataResponse(soap, &out);
	soap_default_omws__getProjectionMetadata(soap, &soap_tmp_omws__getProjectionMetadata);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getProjectionMetadata(soap, &soap_tmp_omws__getProjectionMetadata, "omws:getProjectionMetadata", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getProjectionMetadata(soap, soap_tmp_omws__getProjectionMetadata.ticket, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getProjectionMetadataResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getProjectionMetadataResponse(soap, &out, "omws:getProjectionMetadataResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getProjectionMetadataResponse(soap, &out, "omws:getProjectionMetadataResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__evaluateModel(struct soap *soap)
{	struct omws__evaluateModel soap_tmp_omws__evaluateModel;
	struct omws__evaluateModelResponse soap_tmp_omws__evaluateModelResponse;
	soap_default_omws__evaluateModelResponse(soap, &soap_tmp_omws__evaluateModelResponse);
	soap_default_omws__evaluateModel(soap, &soap_tmp_omws__evaluateModel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__evaluateModel(soap, &soap_tmp_omws__evaluateModel, "omws:evaluateModel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__evaluateModel(soap, soap_tmp_omws__evaluateModel.om__ModelEvaluationParameters, soap_tmp_omws__evaluateModelResponse.ticket);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__evaluateModelResponse(soap, &soap_tmp_omws__evaluateModelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__evaluateModelResponse(soap, &soap_tmp_omws__evaluateModelResponse, "omws:evaluateModelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__evaluateModelResponse(soap, &soap_tmp_omws__evaluateModelResponse, "omws:evaluateModelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getModelEvaluation(struct soap *soap)
{	struct omws__getModelEvaluation soap_tmp_omws__getModelEvaluation;
	struct omws__modelEvaluationResponse out;
	soap_default_omws__modelEvaluationResponse(soap, &out);
	soap_default_omws__getModelEvaluation(soap, &soap_tmp_omws__getModelEvaluation);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getModelEvaluation(soap, &soap_tmp_omws__getModelEvaluation, "omws:getModelEvaluation", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getModelEvaluation(soap, soap_tmp_omws__getModelEvaluation.ticket, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__modelEvaluationResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__modelEvaluationResponse(soap, &out, "omws:modelEvaluationResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__modelEvaluationResponse(soap, &out, "omws:modelEvaluationResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__samplePoints(struct soap *soap)
{	struct omws__samplePoints soap_tmp_omws__samplePoints;
	struct omws__samplePointsResponse soap_tmp_omws__samplePointsResponse;
	soap_default_omws__samplePointsResponse(soap, &soap_tmp_omws__samplePointsResponse);
	soap_default_omws__samplePoints(soap, &soap_tmp_omws__samplePoints);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__samplePoints(soap, &soap_tmp_omws__samplePoints, "omws:samplePoints", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__samplePoints(soap, soap_tmp_omws__samplePoints.om__SamplingParameters, soap_tmp_omws__samplePointsResponse.ticket);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__samplePointsResponse(soap, &soap_tmp_omws__samplePointsResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__samplePointsResponse(soap, &soap_tmp_omws__samplePointsResponse, "omws:samplePointsResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__samplePointsResponse(soap, &soap_tmp_omws__samplePointsResponse, "omws:samplePointsResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getSamplingResult(struct soap *soap)
{	struct omws__getSamplingResult soap_tmp_omws__getSamplingResult;
	struct omws__getSamplingResultResponse out;
	soap_default_omws__getSamplingResultResponse(soap, &out);
	soap_default_omws__getSamplingResult(soap, &soap_tmp_omws__getSamplingResult);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getSamplingResult(soap, &soap_tmp_omws__getSamplingResult, "omws:getSamplingResult", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getSamplingResult(soap, soap_tmp_omws__getSamplingResult.ticket, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getSamplingResultResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getSamplingResultResponse(soap, &out, "omws:getSamplingResultResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getSamplingResultResponse(soap, &out, "omws:getSamplingResultResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__runExperiment(struct soap *soap)
{	struct omws__runExperiment soap_tmp_omws__runExperiment;
	struct omws__runExperimentResponse out;
	soap_default_omws__runExperimentResponse(soap, &out);
	soap_default_omws__runExperiment(soap, &soap_tmp_omws__runExperiment);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__runExperiment(soap, &soap_tmp_omws__runExperiment, "omws:runExperiment", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__runExperiment(soap, soap_tmp_omws__runExperiment.om__ExperimentParameters, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__runExperimentResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__runExperimentResponse(soap, &out, "omws:runExperimentResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__runExperimentResponse(soap, &out, "omws:runExperimentResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__getResults(struct soap *soap)
{	struct omws__getResults soap_tmp_omws__getResults;
	struct omws__getResultsResponse out;
	soap_default_omws__getResultsResponse(soap, &out);
	soap_default_omws__getResults(soap, &soap_tmp_omws__getResults);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__getResults(soap, &soap_tmp_omws__getResults, "omws:getResults", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__getResults(soap, soap_tmp_omws__getResults.tickets, &out);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__getResultsResponse(soap, &out);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__getResultsResponse(soap, &out, "omws:getResultsResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__getResultsResponse(soap, &out, "omws:getResultsResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_omws__cancel(struct soap *soap)
{	struct omws__cancel soap_tmp_omws__cancel;
	struct omws__cancelResponse soap_tmp_omws__cancelResponse;
	soap_default_omws__cancelResponse(soap, &soap_tmp_omws__cancelResponse);
	soap_default_omws__cancel(soap, &soap_tmp_omws__cancel);
	soap->encodingStyle = NULL;
	if (!soap_get_omws__cancel(soap, &soap_tmp_omws__cancel, "omws:cancel", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = omws__cancel(soap, soap_tmp_omws__cancel.tickets, soap_tmp_omws__cancelResponse.cancelledTickets);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_omws__cancelResponse(soap, &soap_tmp_omws__cancelResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_omws__cancelResponse(soap, &soap_tmp_omws__cancelResponse, "omws:cancelResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_omws__cancelResponse(soap, &soap_tmp_omws__cancelResponse, "omws:cancelResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

} // namespace omws


#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of omwsServer.cpp */
