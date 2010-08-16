// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2009 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Authors: Francesco Rea
 * email:   francesco.rea@iit.it
 * website: www.robotcub.org 
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

/**
 * @file saliencyBlobFinderModule.h
 * @brief module class definition for the blob finder module.
 */

#ifndef _SALIENCYBLOBFINDERMODULE_H_
#define _SALIENCYBLOBFINDERMODULE_H_

/** 
 * @ingroup icub_module
 *
 * \defgroup icub_saliencyBlobFinder saliencyBlobFinder
 *
 * This is a a blob finder module that works on logpolar images. It takes an edge image as input (e.g. as produced by the
 * visualFilter module), runs the watershed operator (to find blobs), quantizes the colors and then computes a measure
 * of saliency for each blob. The output can be used and combined with other image based measures of saliency.
 * 
 * More in details, this module extracts visual blobs in the scene and gives a saliency value to any of them.
 * The process of assigning a saliency value is based on a top-down algorithm and bottom-up algorithm.(see <a href="http://">here</a>).
 * The bottom-up gives high saliency to isolated blobs whereas the top-down gives high saliency to blobs which have mean colour close to 
 * the target colour. The module receives an edge image and the respective red plane, green plane and yellow plane. It needs the opponency 
 * maps composed as R+G-, G+R-, B+Y- as well. These are maps made by the difference of gaussians appied on the three colour planes and
 * represent colour sensitive photoreceptors of the human visual system. Subsequently, the module applies a watershed method to 
 * segment blobs from the image and calculates a saliency map based on the mean color of the blob, its dimension and the the color distance 
 * to the target object (in case of top-down attention).
 *
 * \section intro_sec Description
 * Speicfically, the module:
 * - stream the mean color image of all the blobs\n
 * - stream the image of the fovea blob\n
 * - stream the saliency map as a gray scale image\n
 * - stream the most salient blob\n
 * 
 * \image html saliencyBlobFinder.png
 *
 * \section lib_sec Libraries
 *
 * YARP\n
 * IPP
 *
 * \section parameters_sec Parameters
 * Here is a  comprehensive list of the parameters you can pass to the module.\n
 * --name (string) name of the module. The name of all the ports will be istantiated starting from this name\n
 * --from (string) name of the configuration file.\n
 * --context (string) name of the application\n
 * 
 * \section portsa_sec Ports Accessed
 * - /blobFinderInterface/command:o : once manually connected to the <name>/cmd the graphical interface is able to control this module (for further information press Help Button in the interface)\n
 * - /visualFilter/rg:o :  colour opponency map of the input image (difference of gaussian)\n
 * - /visualFilter/gr:o : colour opponency map of the input image (difference of gaussian)\n
 * - /visualFilter/by:o : colour opponency map of the input image (difference of gaussian)\n
 * - /visualFilter/edges:o : edges extracted from the input image\n
 *
 * \section portsc_sec Ports Created
 * - <name>/cmd
 * - <name>/image:i
 * - <name>/rg:i
 * - <name>/gr:i
 * - <name>/by:i
 * - <name>/image:o
 * - <name>/centroid:o
 *
 * Output ports:
 * - <name>/image:o: image output
 * - <name>/centroid:o : position of the cog of the most salient blob
 * - <name>/gazeControl:o : position of the cog of the most salient blob
 *
 * Input ports:
 * - <name>/image:i: input ports which takes as input a yarp::sig::ImageOf<PixelRgb>\n
 * - <name>/rg:i: acquires the input stream of the R+G- opponency map\n
 * - <name>/gr:i: acquires the input stream of the G+R- opponency map\n
 * - <name>/by:i: acquires the input stream of th B+Y- opponency map\n
 * 
 * InOut ports:
 * - <name>/cmd : port for the input rpc commands (for further command send Help command)
 * 
 * This module is able to respond to the following set of commands:
 * - set mea: select the output which represents all the blobs in mean colour\n
 * - set tag: select the output which represents all the blobs\n
 * - set max: select the output which represents the most salient blob\n
 * - set clp: select the output which represents all the blobs intensified by the saliency\n
 * - set fov: select the output which represents the fovea blob\n
 *
 * - set kbu: weight of the bottom-up algorithm\n
 * - set ktd: weight of top-down algorithm\n
 * - set rin: red intensity value\n
 * - set gin: green intensity value\n
 * - set bin: blue intensity value\n
 * - set Mdb: Maximum dimension of the blob analysed\n
 * - set mdb: minimum dimension of the blob analysed\n
 * - set tco: set the timeconstant in second for output format (x y z) 3d space\n
 * - set tce: set the time constant in second for output forma (img x y) imageplane\n
 * - set mBA: set minimum bounding area\n
 * - set pAR: set percentage of the blob dimension considered surrounding area\n
 * 
 * - rset flt : reset the filter\n
 *
 * - get kbu: weight of the bottom-up algorithm\n
 * - get ktd: weight of top-down algorithm\n
 * - get rin: red intensity value\n
 * - get gin: green intensity value\n
 * - get bin: blue intensity value\n
 * - get Mdb: Maximum dimension of the blob analysed\n
 * - get mdb: minimum dimension of the blob analysed\n
 * 
 *
 * \section in_files_sec Input Data Files
 *
 * None
 *
 * \section out_data_sec Output Data Files
 *
 * None
 *
 * \section conf_file_sec Configuration Files
 *
 * \c saliencyBlobFinderLeft.ini in \c $ICUB_ROOT/app/logpolarAttention/conf \n
 * 
 * \section tested_os_sec Tested OS
 *
 * Windows, Linux
 *
 * \section example_sec Example Instantiation of the Module
 * <tt>saliencyBlobFinder --from saliencyBlobFinder.ini --context attentionMechanism/conf --name /blobFinder/icub/left_cam</tt>
 *
 * \author Francesco Rea, Giorgio Metta, based on existing code by Francesco Orabona
 * 
 * Copyright (C) 2009 RobotCub Consortium\n
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.\n
 * This file can be edited at \c $ICUB_ROOT/main/src/examples/demoModule/include/iCub/myModule.h
 * 
 */

#include <iostream>
#include <map>

#include <ippi.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <iCub/blobFinderThread.h>

// general command vocab's
#define COMMAND_VOCAB_HELP VOCAB4('h','e','l','p')
#define COMMAND_VOCAB_RSET VOCAB4('r','s','e','t')
#define COMMAND_VOCAB_FLT VOCAB3('f','l','t')
#define COMMAND_VOCAB_SET VOCAB3('s','e','t')
#define COMMAND_VOCAB_GET VOCAB3('g','e','t')
#define COMMAND_VOCAB_RUN VOCAB3('r','u','n')
#define COMMAND_VOCAB_IS VOCAB2('i','s')
#define COMMAND_VOCAB_FAILED VOCAB4('f','a','i','l')
#define COMMAND_VOCAB_OK VOCAB2('o','k')
#define COMMAND_VOCAB_CHILD_COUNT VOCAB2('c','c')

#define COMMAND_VOCAB_NAME VOCAB2('s','1')
#define COMMAND_VOCAB_CHILD_NAME VOCAB2('c','n')
#define COMMAND_VOCAB_SALIENCE_THRESHOLD VOCAB2('t','h')
#define COMMAND_VOCAB_NUM_BLUR_PASSES VOCAB2('s','2')
#define COMMAND_VOCAB_RGB_PROCESSOR VOCAB3('r','g','b')
#define COMMAND_VOCAB_YUV_PROCESSOR VOCAB3('y','u','v')
// command vocab for the output produced
#define COMMAND_VOCAB_MEANCOLOURS VOCAB3('m','e','a')
#define COMMAND_VOCAB_TAGGED VOCAB3('t','a','g')
#define COMMAND_VOCAB_MAXSALIENCY VOCAB3('m','a','x')
#define COMMAND_VOCAB_CONTRASTLP VOCAB3('c','l','p')
#define COMMAND_VOCAB_FOVEA VOCAB3('f','o','v')
#define COMMAND_VOCAB_WAT VOCAB3('w','a','t')
#define COMMAND_VOCAB_PAR VOCAB3('p','a','r')
// other commands
#define COMMAND_VOCAB_TCON VOCAB3('t','c','o')  // time contant for the controlGaze2
#define COMMAND_VOCAB_TCEN VOCAB3('t','c','e')  // time constant for the iKinGazeCtrl


#define COMMAND_VOCAB_KBU VOCAB3('k','b','u')   // weight of the bottom-up algorithm
#define COMMAND_VOCAB_KTD VOCAB3('k','t','d')   // weight of top-down algorithm
#define COMMAND_VOCAB_RIN VOCAB3('r','i','n')   // red intensity value
#define COMMAND_VOCAB_GIN VOCAB3('g','i','n')   // green intensity value
#define COMMAND_VOCAB_BIN VOCAB3('b','i','n')   // blue intensity value
#define COMMAND_VOCAB_MAXDB VOCAB3('M','d','b') // maximum dimension of the blob drawn
#define COMMAND_VOCAB_MINDB VOCAB3('m','d','b') // minimum dimension of the blob drawn
#define COMMAND_VOCAB_MBA VOCAB3('m','B','A')   // minimum dimension of the bounding area
#define COMMAND_VOCAB_STH VOCAB3('s','t','h')   // minimum dimension of the bounding area

// directional saliency filter vocab's
#define COMMAND_VOCAB_DIRECTIONAL_NUM_DIRECTIONS VOCAB3('d','n','d')
#define COMMAND_VOCAB_DIRECTIONAL_NUM_SCALES VOCAB3('d','n','s')
#define COMMAND_VOCAB_DIRECTIONAL_DBG_SCALE_INDEX VOCAB3('d','s','i')
#define COMMAND_VOCAB_DIRECTIONAL_DBG_DIRECTION_INDEX VOCAB3('d','d','i')
#define COMMAND_VOCAB_DIRECTIONAL_DBG_IMAGE_ARRAY_NAMES VOCAB4('d','a','n','s')
#define COMMAND_VOCAB_DIRECTIONAL_DBG_IMAGE_ARRAY_NAME VOCAB3('d','a','n')

/*
 * LATER: proper Doxygen documentation.
 */
class saliencyBlobFinderModule : public yarp::os::RFModule{
private:
    Port cmdPort;               // port necessary for rpc commands
    int rateThread;             // rateThread of the processor Thread
    int minBoundingArea;        // minimum bounding area around the blob for neighbourhood definition
    IppiSize srcsize;           // ipp reference to the size of the input image
    
    int width;                  // width of the input image
    int height;                 // height of the input image
    int countSpikes;            // number spikes that have to be counted before the maxSaliency blob can be choosen
    int xdisp;                  // dispacement on the x axis for the target
    int ydisp;                  // dispacement on the y axis for the target
    
    bool reinit_flag;           // flag that indicates when the reinitiazation has already be done
    
    Semaphore mutex;            // semaphore for the respond function
    blobFinderThread* blobFinder; //main thread responsable to process the input images and produce an output
    Bottle* command;            // bottle where the command received is saved ready for the respond
    Bottle* reply;              // bottle where the reply will be stored for further purpose

    std::map<const char*,int> occurencesMap; //map of the occurences of control positions
    std::string moduleName;     // name of the module read from configuration 
    int thresholdArea;          // max dimension of the area in order to consider the blob interesting

    /**
    * copy flags to the blobFinder thread
    */
    void copyFlags();

    bool contrastLP_flag;           // flag for drawing contrastLP
    bool meanColour_flag;           // flag for drawing meanColourImage
    bool blobCataloged_flag;        // flag for drawing blobCatalog
    bool foveaBlob_flag;            // flag for drawing foveaBlob
    bool colorVQ_flag;              // flag for drawing colorVQ
    bool maxSaliencyBlob_flag;      // flag for drawing maxSaliencyBlob
    bool blobList_flag;             // flag for drawing blobList
    bool tagged_flag;               // flag for the drawings
    bool watershed_flag;            // flag for drawing watershed image
    bool timeControl_flag;          // it indicates if the control of the time is on
    bool filterSpikes_flag;         // indicates if the process that filters the spikes is on

public:
    /**
    * default constructor
    */
    saliencyBlobFinderModule();
    
    /**
    * destructor
    */
    ~saliencyBlobFinderModule(){};
    
    /**
     * open the port and intialise the module
     * @param config configuration of the module
     */
    bool open(Searchable& config); 
    
    /**
     * tries to interrupt any communications or resource usage
     */
    bool interruptModule(); // 
    
    /**
     * function that set the options detected from the command line
     * @param opt options passed to the module
     */
    void setOptions(yarp::os::Property opt);
    
    /**
     * function for initialization and configuration of the RFModule
     * @param rf resourceFinder reference
     * @return true iff ???
     */
    virtual bool configure(yarp::os::ResourceFinder &rf);
    
    /**
     * catches all the commands that have to be executed when the module is closed
     * @return ...
     */
    bool close(); 
    
    /**
     * function that reinitiases some attributes of the class
     * @param width width of the input image
     * @param height height of the input image
     */
    void reinitialise(int width,int height);
    
    /**
     * respond to command coming from the command port
     * @param command command received by the module
     * @param reply answer that this module gives to the command (if any)
     * @return
     */
    bool respond(const Bottle &command,Bottle &reply);
    
    /**
     * updates the module
     * return true iff...
     */
    bool updateModule();
    
    /**
     * function that streams the images out on the ports
     */
    void outPorts();
};

#endif //__SALIENCYBLOBFINDERMODULE_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------
