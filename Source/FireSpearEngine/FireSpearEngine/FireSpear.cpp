#include "FireSpear.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define MB 1000000


FireSpear::FireSpear()
{
	gameObjectManager = new GameObjectManager();
	physicEngine = new PhysicEngine(gameObjectManager);
	scriptingSystem = new ScriptingSystem(gameObjectManager);
	inputSystem = new InputSystem(gameObjectManager);
	sceneManager = new SceneManager(gameObjectManager);
	//std::cout << "DEBUG: CREATE NEW ENGINE" << std::endl;
}

FireSpear::~FireSpear()
{
	//std::cout << "DEBUG: DESTROY NEW ENGINE" << std::endl;
	delete physicEngine;
	delete gameObjectManager;
	delete scriptingSystem;
	delete inputSystem;
	delete sceneManager;
}

bool FireSpear::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters = diskSpaceNeeded / ((diskfree.sectors_per_cluster) * diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters)
	{
		MessageBox(NULL,
			"CheckStorage Failure: Not enough physical storage.", // THE MESSAGE INSIDE THE WINDOW
			"Check Storage Failed", // THE MESSAGE ON THE TOP
			NULL);
		return false;
	}
	std::cout << "STORAGE CHECKING SUCCEEDED !!!" << std::endl;
	std::cout << std::endl;
	return true;
}

bool FireSpear::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);


	// CHECK PHYSICAL RAM
	if (status.ullTotalPhys < physicalRAMNeeded)
	{

		MessageBox(NULL,
			"Not enough physical memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}

	// CHECK VIRTUAL RAM
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{

		MessageBox(NULL,
			"Not enough virtual memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}


	// CHECK CONTIGUIS MEMORY
	char* buff = new char[virtualRAMNeeded];

	if (buff) delete[] buff;
	else
	{

		MessageBox(NULL,
			"Not enough contiguous memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}

	std::cout << "MEMORY CHECKING SUCCEEDED !!!" << std::endl;

	printf("Available RAM: %I64d \n", status.ullAvailPhys / 1048576);
	printf("Available Virtual Memory: %I64d \n", status.ullAvailVirtual / 1048576);

	std::cout << std::endl;

	return true;
}

bool FireSpear::IsOnlyInstance(LPCTSTR gameTitle)
{
	handle = CreateMutex(NULL, TRUE, gameTitle);
	

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hwnd = FindWindow(gameTitle, NULL);
		if (hwnd)
		{
			std::cout << "Found window!" << std::endl;
			MessageBox(NULL,
				"There is another instance",
				"Muti-Instances Detected",
				NULL);

			ShowWindow(hwnd, SW_SHOWNORMAL);
			SetFocus(hwnd);
			SetForegroundWindow(hwnd);
			SetActiveWindow(hwnd);
			return false;
		}
		MessageBox(NULL,
			"There is another instance",
			"Muti-Instances Detected",
			NULL);
		return false;
	}
	OutputDebugString("CHECK MUTI-INSTANCES SUCCESS");
	OutputDebugStringW(L"\n");
	return true;
}

bool FireSpear::IsOnlyInstance(bool window)
{
	//std::cout << "DEBUG: WINDOW: " << window << std::endl;
	if (window)
	{
		MessageBox(NULL,
			"There is another instance",
			"Muti-Instances Detected",
			NULL);
		std::cout << "Window open" << std::endl;
		return false;
	}

	return true;
}

const char* FireSpear::ReadCPUArchitecture()
{
	char CPUName[255];
	DWORD BufSize2 = sizeof(CPUName);
	DWORD type2 = REG_SZ;
	HKEY hKey2;

	long lError2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey2);

	if (lError2 == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey2, "ProcessorNameString", NULL, &type2, (LPBYTE)& CPUName, &BufSize2);
	}

	std::cout << "CPU Architecture: " + (std::string)CPUName << std::endl;
	return CPUName;
}

DWORD FireSpear::ReadCPUSpeed()
{

	DWORD dwMHz;
	DWORD BufSize = sizeof(dwMHz);
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)& dwMHz, &BufSize);
	}



	printf("CPU Speed: %d\n", dwMHz);
	return dwMHz;
}

void FireSpear::InitilizeSystem()
{
	//std::cout << "DEBUG: GAME IS INITIALIZING" << std::endl;
	if (IsOnlyInstance("Fire Spear Engine")) // IF THE NAME IS UNIQUE
	{
		std::cout << "Welcome to Fire Spear Engine" << std::endl;
		std::cout << std::endl;

		if (CheckMemory(3 * MB, 3 * MB))
		{
			if (CheckStorage(31450000)) // 31.45Mb
			{
				ReadCPUSpeed();
				ReadCPUArchitecture();
				_gameState = FireSpear::ShowingSplash;
				
				return;
			}
		}
	}
	//std::cout << "DEBUG: GAME IS UNINITIALIZED" << std::endl;
	_gameState = FireSpear::Uninitialized;
}

void FireSpear::CreateEngineWindow(std::string windowTitle, int width, int height)
{
	_mainWindow.create(sf::VideoMode(width, height), windowTitle);
	//std::cout << "DEBUG: WINDOW CREATED" << std::endl;
}

void FireSpear::CreateSplashScreen(sf::RenderWindow& window)
{
	sf::Image backgroundImg;
	sf::Texture backgroundTex;
	if (backgroundImg.loadFromFile("../../../Assets/Images/NeZhas_Logo.png") != true) {
		return;
	}
	backgroundTex.loadFromImage(backgroundImg);
	sf::Sprite slashScreen(backgroundTex);

	sf::Clock clock;
	sf::Time time;
	window.draw(slashScreen);
	window.display();

	while (_gameState != GameState::Initialized)
	{
		time += clock.restart();
		if (time > sf::seconds(0.5f))
		{
			return;
		}
	}

}

void FireSpear::Run()
{
	if (_gameState == Uninitialized)
		return;

	CreateEngineWindow("Fire Spear Engine", SCREEN_WIDTH, SCREEN_HEIGHT);
	_gameState = Playing;

	CreateSplashScreen(_mainWindow);
	InstantiateSystems();

	Awake();
	Start();

	Tick();
	_mainWindow.close();
}

void FireSpear::Pause()
{
	_gameState = Paused;
}

void FireSpear::Tick()
{
	sf::Clock clock;
	sf::Time timeSinceLastFrame;

	while (_mainWindow.isOpen())
	{
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame > FPS)
		{
			timeSinceLastFrame -= FPS;
			FixUpdate();
		}

		ProcessEvent();
		Update(timeSinceLastFrame);
		Render();
	}
}

void FireSpear::Awake()
{
	//std::cout << "DEBUG: ENGINE AWAKE FUNCTION RUNNING" << std::endl;
	
	gameObjectManager->Awake();
	scriptingSystem->Awake();
	inputSystem->Awake();
	physicEngine->Awake();
	
}

void FireSpear::Start()
{

	physicEngine->Start();
	gameObjectManager->Start();
	scriptingSystem->Start();
	inputSystem->Start();
}

void FireSpear::Update(sf::Time deltaTime)
{
	if (_gameState == Playing)
	{
		gameObjectManager->Update(deltaTime);
		scriptingSystem->Update(deltaTime);
		inputSystem->Update(deltaTime);
	}
}

void FireSpear::FixUpdate()
{
	if (_gameState == Playing)
	{
		physicEngine->FixedUpdate(FPS);
	}
	
}

void FireSpear::Render()
{
	_mainWindow.clear(sf::Color(255, 230, 171, 100));
	for (const auto& p : gameObjectManager->DrawableObjects())
	{
		RenderComponent* r = p->GetComponent<RenderComponent*>();
		
		_mainWindow.draw(r->GetShape(), sf::RenderStates(r->GetTransform()));
	}
	_mainWindow.display();
}

void FireSpear::ProcessEvent()
{
	sf::Event event;
	while (_mainWindow.pollEvent(event))
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			isRunning = false;
			_mainWindow.close();
			//gameObjectManager->DeleteAllGameObjects();
			for (auto g : gameObjectManager->gameObjects)
			{
				g.second->GetComponent<AudioPlayerComponent*>()->Stop();
			}
			if (CloseHandle(handle)) {
			}
			break;

		case sf::Event::KeyPressed:
			KeyboardInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			KeyboardInput(event.key.code, false);
			break;

		default:
			break;
		}

	}
}

void FireSpear::KeyboardInput(sf::Keyboard::Key keyCode, bool isPressed)
{
	switch (keyCode)
	{
	case sf::Keyboard::Space:
		if (isPressed)
		{
			_gameState = Playing;
		}
		break;

	default:
		break;
	}
}

void FireSpear::InstantiateSystems()
{
	physicEngine->Instantiate();
	scriptingSystem->Instantiate();
	inputSystem->Instantiate();
}

bool FireSpear::IsExiting()
{
	if (_mainWindow.isOpen())
		return false;
	return true;
}

