#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "pointlight.h"



using namespace std;


int main()
{
    string path = "/home/formation/cours/solarsystem";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();


/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);



    // Create the Sun
        PointLight sunLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f,1.0f), 2500.0f);
        sunLight.Bind(shader);

        Texture sunTexture(path + "/planets/sun.jpg");

        sunTexture.Bind(0);  

        shader.setUniform1i("textureSampler", 0);


        /////////////////////////Création de la fenêtre IMGUI/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            UserInterface ui(&sunLight, window);

NavigationControls controls(window, &cam, ui);
        // Set scales and distances
        float sunScale = 20.0f;
        float earthScale = 1.0f;

        // Average diameters of planets in kilometers
        float earthDiameter = 12742.0f;  // Earth's diameter

        // Calculate scale factors for each planet relative to Earth
        float mercureScale = (4879.0f / earthDiameter * earthScale)*1.5;
        float venusScale = 12104.0f / earthDiameter * earthScale;    
        float marsScale = 6779.0f / earthDiameter * earthScale;      
        float jupiterScale = (139820.0f / earthDiameter * earthScale)*0.5; 
        float saturnScale = (116460.0f / earthDiameter * earthScale)*0.5;  
        float uranusScale = 50724.0f / earthDiameter * earthScale;    
        float neptuneScale = 49244.0f / earthDiameter * earthScale;   
        float plutoScale = (2376.6f / earthDiameter * earthScale)*10;     

        float earthDistance = 100.0f;

        // Average distances from the sun to planets in millions of kilometers
        float mercureDistance = 57.91f;  
        float venusDistance = 108.2f;           
        float marsDistance = 227.9f;           
        float jupiterDistance = 778.5f;  
        float saturnDistance = 1433.4f;   
        float uranusDistance = 2872.5f;   
        float neptuneDistance = 4495.1f;  
        float plutoDistance = 5906.4f;            
        // Calculating distance factors for each planet relative to Earth
        mercureDistance = mercureDistance / 149.6f * earthDistance;
        venusDistance = venusDistance / 149.6f * earthDistance;
        marsDistance = marsDistance / 149.6f * earthDistance;
        jupiterDistance = (jupiterDistance / 149.6f * earthDistance)/2;
        saturnDistance = (saturnDistance / 149.6f * earthDistance)/2;
        uranusDistance = (uranusDistance / 149.6f * earthDistance)/5;
        neptuneDistance = (neptuneDistance / 149.6f * earthDistance)/5;
        plutoDistance = (plutoDistance / 149.6f * earthDistance)/5;


        // Setting initial angles for orbits
        float mercureOrbitAngle = 0.0f;
        float venusOrbitAngle = 0.0f;
        float earthOrbitAngle = 0.0f;
        float marsOrbitAngle = 0.0f;
        float jupiterOrbitAngle = 0.0f;
        float saturnOrbitAngle = 0.0f;
        float uranusOrbitAngle = 0.0f;
        float neptuneOrbitAngle = 0.0f;
        float plutoOrbitAngle = 0.0f;


        Object sun(path + "/planets/sphere.obj", path + "/planets/sun.jpg");
        sun.position = sunLight.getPosition();
        sun.scaleFactor = sunScale;
        cam.computeMatrices(width, height);
        glm::mat4 m = sun.getModelMatrix();
        glm::mat4 v = cam.getViewMatrix();
        glm::mat4 p = cam.getProjectionMatrix();
        glm::mat4 mvp = p * v * m;

        Object sky(path + "/planets/cube.obj", path + "/planets/sky.jpg");
        sky.position = glm::vec3(0.0f,0.0f,0.0f);
        sky.scaleFactor = 10000;




        Object mercure(path + "/planets/sphere.obj", path + "/planets/mercury.jpg");
        mercure.scaleFactor = mercureScale;

        Object venus(path + "/planets/sphere.obj", path + "/planets/venus.jpg");
        venus.scaleFactor = venusScale;


        Object earth(path + "/planets/sphere.obj", path + "/planets/earth.jpg");
        earth.scaleFactor = earthScale;

        Object mars(path + "/planets/sphere.obj", path + "/planets/mars.jpg");
        mars.scaleFactor = marsScale;

        Object jupiter(path + "/planets/sphere.obj", path + "/planets/jupiter.jpg");
        jupiter.scaleFactor = jupiterScale;

        Object saturn(path + "/planets/sphere.obj", path + "/planets/saturn.jpg");
        saturn.scaleFactor = saturnScale;

        Object uranus(path + "/planets/sphere.obj", path + "/planets/uranus.jpg");
        uranus.scaleFactor = uranusScale;

        Object neptune(path + "/planets/sphere.obj", path + "/planets/neptune.jpg");
        neptune.scaleFactor = neptuneScale;

        Object pluto(path + "/planets/sphere.obj", path + "/planets/pluto.jpg");
        pluto.scaleFactor = plutoScale;

/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;
    // Orbital periods in Earth years
    float mercureOrbitalPeriod = 0.24f;
    float venusOrbitalPeriod = 0.62f;
    float earthOrbitalPeriod = 1.0f;
    float marsOrbitalPeriod = 1.88f;
    float jupiterOrbitalPeriod = 11.86f;
    float saturnOrbitalPeriod = 29.46f;
    float uranusOrbitalPeriod = 84.02f;
    float neptuneOrbitalPeriod = 164.8f;
    float plutoOrbitalPeriod = 248.1f;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){
        renderer.Clear();
        shader.Bind();
        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;

        mercureOrbitAngle += 2 * glm::pi<float>() / (mercureOrbitalPeriod*1000/ui.m_rotationSpeed);
        venusOrbitAngle += 2 * glm::pi<float>() / (venusOrbitalPeriod*1000/ui.m_rotationSpeed);
        earthOrbitAngle += 2 * glm::pi<float>() / (earthOrbitalPeriod*1000/ui.m_rotationSpeed);
        marsOrbitAngle += 2 * glm::pi<float>() / (marsOrbitalPeriod*1000/ui.m_rotationSpeed);
        jupiterOrbitAngle += 2 * glm::pi<float>() / (jupiterOrbitalPeriod*1000/ui.m_rotationSpeed);
        saturnOrbitAngle += 2 * glm::pi<float>() / (saturnOrbitalPeriod*1000/ui.m_rotationSpeed);
        uranusOrbitAngle += 2 * glm::pi<float>() / (uranusOrbitalPeriod*1000/ui.m_rotationSpeed);
        neptuneOrbitAngle += 2 * glm::pi<float>() / (neptuneOrbitalPeriod*1000/ui.m_rotationSpeed);
        plutoOrbitAngle += 2 * glm::pi<float>() / (plutoOrbitalPeriod*1000/ui.m_rotationSpeed);
        sun.rotationAngles.y=currentTime;
        mercure.rotationAngles.y=currentTime;
        venus.rotationAngles.y=currentTime;
        jupiter.rotationAngles.y=currentTime;
        earth.rotationAngles.y=currentTime;
        mars.rotationAngles.y = currentTime;
        saturn.rotationAngles.y=currentTime;
        uranus.rotationAngles.y=currentTime;
        neptune.rotationAngles.y=currentTime;
        pluto.rotationAngles.y = currentTime;


        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);

        // Draw the sky
        m = sky.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, sky, shader);


        // Draw the Sun
        m = sun.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, sun, shader);
//////////////////////////////draw pllanets/////////////////////////////////////////
        glm::vec3 mercurePosition(mercureDistance * cos(mercureOrbitAngle), 0.0f, mercureDistance * sin(mercureOrbitAngle));
        mercure.position = mercurePosition;
        m = mercure.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, mercure, shader);

        glm::vec3 venusPosition(venusDistance * cos(venusOrbitAngle), 0.0f, venusDistance * sin(venusOrbitAngle));
        venus.position = venusPosition;
        m = venus.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, venus, shader);



//         Draw Earth
        glm::vec3 earthPosition(earthDistance * cos(earthOrbitAngle), 0.0f, earthDistance * sin(earthOrbitAngle));
        earth.position = earthPosition;
        m = earth.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, earth, shader);


        // Draw Mars
        glm::vec3 marsPosition(marsDistance * cos(marsOrbitAngle), 0.0f, marsDistance * sin(marsOrbitAngle));
        mars.position = marsPosition;
        m = mars.getModelMatrix();
        mvp = p * v * m;
        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, mars, shader);



        glm::vec3 jupiterPosition(jupiterDistance * cos(jupiterOrbitAngle), 0.0f, jupiterDistance * sin(jupiterOrbitAngle));
        jupiter.position = jupiterPosition;
        m = jupiter.getModelMatrix();
        mvp = p * v * m;
        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, jupiter, shader);



        glm::vec3 saturnPosition(saturnDistance * cos(saturnOrbitAngle), 0.0f, saturnDistance * sin(saturnOrbitAngle));
        saturn.position = saturnPosition;
        m = saturn.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, saturn, shader);

        glm::vec3 uranusPosition(uranusDistance * cos(uranusOrbitAngle), 0.0f, uranusDistance * sin(uranusOrbitAngle));
        uranus.position = uranusPosition;
        m = uranus.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, uranus, shader);

        glm::vec3 neptunePosition(neptuneDistance * cos(neptuneOrbitAngle), 0.0f, neptuneDistance * sin(neptuneOrbitAngle));
        neptune.position = neptunePosition;
        m = neptune.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, neptune, shader);

        glm::vec3 plutoPosition(plutoDistance * cos(plutoOrbitAngle), 0.0f, plutoDistance * sin(plutoOrbitAngle));
        pluto.position = plutoPosition;
        m = pluto.getModelMatrix();
        mvp = p * v * m;

        shader.setUniformMat4f("M", m);
        shader.setUniformMat4f("MVP", mvp);
        renderer.Draw(va, pluto, shader);
        ui.Bind(&shader);
        ui.Draw();
        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();




    return 0;
}
