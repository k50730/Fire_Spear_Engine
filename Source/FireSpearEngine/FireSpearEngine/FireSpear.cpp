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
}

FireSpear::~FireSpear()
{
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
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hwnd = FindWindow(gameTitle, NULL);
		if (hwnd)
		{

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
	_gameState = FireSpear::Uninitialized;
}

void FireSpear::CreateEngineWindow(std::string windowTitle, int width, int height)
{
	_mainWindow.create(sf::VideoMode(width, height), windowTitle);
}

void FireSpear::CreateSplashScreen(sf::RenderWindow& window)
{
	sf::Image backgroundImg;
	sf::Texture backgroundTex;
	if (backgroundImg.loadFromFile("../../Images/NeZhas_Logo.png") != true) {
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
	_gameState = FireSpear::Playing;

	CreateSplashScreen(_mainWindow);
	InstantiateSystems();

	Awake();
	Start();

	Tick();
	_mainWindow.close();
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
	physicEngine->Awake();
	gameObjectManager->Awake();
	scriptingSystem->Awake();
	inputSystem->Awake();
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
	gameObjectManager->Update(deltaTime);
	scriptingSystem->Update(deltaTime);
	inputSystem->Update(deltaTime);
}

void FireSpear::FixUpdate()
{
	physicEngine->FixedUpdate(FPS);
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
			_mainWindow.close();
			break;

		default:
			break;
		}

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

