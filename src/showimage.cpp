#include "glpp/app.hpp"
#include "glpp/draw.hpp"
#include "glpp/gleigen.hpp"
#include "glpp/imageproc.hpp"
#include <Eigen/Geometry>
#include <iostream>
#include <ros/ros.h>


using namespace glpp;
#define COCO_ERR() std::cout
float angle = 0;

bool swap = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
    	swap = true;
    }
}

GLFWwindow* winit(int width,int height, std::string monitorname, bool fullscreen)
{
		
	const char * title = "projector_screen";

	if(!glfwInit())
	{
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	#ifdef GLFW_AUTO_ICONIFY
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
	#endif

	int n;
	
	GLFWmonitor * monitor = 0;

	if(fullscreen)
	{
		if(monitorname.empty())
			monitor =  glfwGetPrimaryMonitor();
		else
		{
			auto monitors = glfwGetMonitors(&n);
			for(int i = 0; i < n; i++)
			{
				if(strcmp(glfwGetMonitorName(monitors[i]),monitorname.c_str()) == 0)
				{
					monitor = monitors[i];
					break;
				}
			}
			if(!monitor)
			{
				std::cout << "cannot find monitor " << monitorname << "\n Listing monitors:\n";
				for(int i = 0; i < n; i++)
					std::cout << " " << i << " " << glfwGetMonitorName(monitors[i]) << std::endl;
				monitor = glfwGetPrimaryMonitor();
			}
		}
	}

	GLFWwindow * window;

	if(width == 0)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);		
		window  = glfwCreateWindow( mode->width, mode->height, title, monitor, NULL);
	}
	else
		window  = glfwCreateWindow( width, height, title, monitor, NULL);

	if(!window)
	{
		std::cout<<"Cannot create window " << width << " " << height << " monitor " << monitor << std::endl;
		return 0;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) 
	{
		return 0;
	}
	return window;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ros_minimal_node");
	ros::NodeHandle nh;
	ros::NodeHandle pnh("~");

	std::string monitor;
	std::string image;
	int width;
	int height;
	bool fullscreen;
	
	pnh.param<std::string>("image",image,"");
	if(image.empty())
	{
		if(argc < 2)
		{	
			std::cout << "required: imagename [monitorname]" << std::endl;
			return -1;
		}	
		image = argv[1];
	}
	pnh.param("width",width,1280);
	pnh.param("height",height,800);
	pnh.param("fullscreen",fullscreen,true);
	pnh.param<std::string>("monitor",monitor,"HDMI-0");

	auto window = winit(width,height,monitor,fullscreen);
	if(!window)
		return -1;
	glERR("opengl:after init app");

	GLImageProc img;
	Texture tex;
	if(!tex.load(image))
		return 0;
		glERR("opengl:posttexload");
	img.init();
		glERR("opengl:GLImageProc init");
	std::cout << "loaded " << tex.size() << " " << tex.realsize() << " flip:" << tex.flipped() << " res:" << (int)tex << std::endl;
		glERR("opengl:load");

	// TODO: make it lambda function
	glfwSetKeyCallback(window, key_callback);
	glClearColor(1.0,1.0,1.0,1.0);

	do {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glERR("opengl:prerender");
		if(swap)
		{
			// LT LB RT RB
			/*std::array<float,8> full({-0.516531,
										0.133457,
										0.726285,
										0.155106,
										0.740697,
	                                    -0.821361,
                                      -0.511139
                                       -0.847909 });	
                                       */	      
			std::array<float,8> full({-0.5,1.0,   -0.5,-1.0,  0.5,1.0,   0.5,-1.0 });
	        img.setVerticesClipSpace(full);
	        swap = false;
		}
        img.runOnScreen(tex);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} 
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
	glfwTerminate();
}
