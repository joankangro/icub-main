/*
 * Copyright (C) 2012 iCub Facility, Istituto Italiano di Tecnologia
 * Authors: Alberto Cardellino
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef FEATUREINTERFACE_HID_H_
#define FEATUREINTERFACE_HID_H_

#include <ace/ACE.h>
#include <yarp/sig/Vector.h>
using namespace yarp::sig;


class IiCubFeature
{
	public:
		virtual	~IiCubFeature() {};
		virtual bool fillData(char *data ) =0;
		virtual Vector * getData() =0;
		virtual bool pushData(yarp::sig::Vector &in) =0;
	    virtual void setId(FEAT_ID &id) { };
};

class IiCubFeatureList
{
	public:

		virtual	~IiCubFeatureList() {};

		// initialize the transceiver
		virtual IiCubFeature * findus(FEAT_ID *id ) =0;
	    IiCubFeature * findus2(FEAT_ID *id );
};

//IiCubFeatureList *getRobotFeatureList_C();

#endif /* FEATUREINTERFACE_HID_H_ */

