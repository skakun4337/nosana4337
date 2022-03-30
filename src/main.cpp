#include <moonbeam/moonbeam.hpp>

void processInput(MoonBeam::Graphics::Window *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  MoonBeam::MoonBeamEngine engine;
  MoonBeam::Core::SystemManager* sm = engine.GetSystemManager();
  MoonBeam::Core::EntityManager* em = engine.GetEntityManager();
  MoonBeam::Core::ComponentManager* cm = engine.GetComponentManager();

  MoonBeam::Graphics::Window* window = engine.CreateWindow(SCR_WIDTH, SCR_HEIGHT);

  MoonBeam::Graphics::GraphicSystem* gs = sm->CreateSystem<MoonBeam::Graphics::GraphicSystem>();

  MoonBeam::Core::Entity* cameraEnt = em->CreateEntity<MoonBeam::Core::Entity>();
  MoonBeam::Transform* cameraTransf = cameraEnt->AddComponent<MoonBeam::Transform>();
  cameraTransf->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
  MoonBeam::Graphics::Camera* cam = cameraEnt->AddComponent<MoonBeam::Graphics::Camera>();
  cam->SetFar(10);

  gs->SetMainCamera(cam);


  MoonBeam::Graphics::ShaderId sid = gs->LoadDrawShader("./shaders/test.vert","./shaders/test.frag");
  MoonBeam::Graphics::MaterialId mid = gs->CreateMaterial();
  gs->BindShaderToMaterial(mid, sid);

  // MoonBeam::Graphics::ComputeShader compute;
  // try {
  //   compute.Load("./shaders/test.comp");
  // } catch(MoonBeam::Core::Exception& e) {
  //   std::cout << e.what() << std::endl;
  //   return -1;
  // }

  // MoonBeam::Graphics::Texture2D *tex = new MoonBeam::Graphics::Texture2D(512,512);

  // MoonBeam::Graphics::ComputeMaterial* compMat = new MoonBeam::Graphics::ComputeMaterial();
  // compMat->SetTexture(GL_TEXTURE0, tex);
  // compMat->SetShader(&compute);
  // compMat->SetWorkGroups(512,512,1);

  MoonBeam::Graphics::TextureId texid = gs->LoadTexture2D("./resources/test_texture.png");
  gs->BindTextureToMaterial(mid, texid, GL_TEXTURE0);

  // MoonBeam::Graphics::Material* drawMat = new MoonBeam::Graphics::Material();
  // drawMat->SetTexture(GL_TEXTURE0, tex);
  // drawMat->SetShader(&shader);

  MoonBeam::Graphics::Vertex v0 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(1.0f, -1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v1 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v2 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(-1.0f,  1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v3 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(1.0f,  1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), MoonBeam::Graphics::zero3);
  
  MoonBeam::Graphics::Vertex v4 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v5 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v6 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), MoonBeam::Graphics::zero3);
  MoonBeam::Graphics::Vertex v7 = MoonBeam::Graphics::Vertex::CreateVertex(glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), MoonBeam::Graphics::zero3);

  MoonBeam::Graphics::Mesh *m1 = new MoonBeam::Graphics::Mesh();
  m1->AddTri(v4, v5, v7);
  m1->AddTri(v5, v6, v7);


  MoonBeam::Graphics::ShaderId sid2 = gs->LoadDrawShader("./shaders/test.vert","./shaders/test3.frag");
  MoonBeam::Graphics::MaterialId mid2 = gs->CreateMaterial();
  gs->BindShaderToMaterial(mid2, sid2);

  MoonBeam::Core::Entity* quad2 = em->CreateEntity<MoonBeam::Core::Entity>();
  MoonBeam::Transform* trasf2 = quad2->AddComponent<MoonBeam::Transform>();
  trasf2->SetPosition(glm::vec3(1,1,-1));
  MoonBeam::Graphics::Model* mod2 = quad2->AddComponent<MoonBeam::Graphics::Model>();
  mod2->SetMaterial(mid2);
  mod2->SetMesh(m1);

  MoonBeam::Core::Entity* quad = em->CreateEntity<MoonBeam::Core::Entity>();
  MoonBeam::Transform* trasf = quad->AddComponent<MoonBeam::Transform>();
  MoonBeam::Graphics::Model* mod = quad->AddComponent<MoonBeam::Graphics::Model>();
  mod->SetMaterial(mid);
  mod->SetMesh(m1);
  
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  while (!window->ShouldClose()) {
    // compMat->Bind();
    // compute.SetFloat("time", (float)glfwGetTime());
    // compMat->Dispatch();

    processInput(window);

    sm->Update();

    trasf->SetRotation(glm::vec3(0,(float)glfwGetTime(),0));
    
    window->SwapBuffers();
    glfwPollEvents();
  }
  
  //glfwTerminate();
  return 0;
}

void processInput(MoonBeam::Graphics::Window *window) {
  if (window->GetKeyPressed(GLFW_KEY_ESCAPE))
    window->Close();
}
