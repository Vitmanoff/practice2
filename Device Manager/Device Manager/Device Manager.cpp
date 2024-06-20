#include <iostream>
#include <Windows.h>
#include <VersionHelpers.h>
#include <string>
#include <dxgi.h>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <set>

#pragma comment(lib, "dxgi.lib")

// Функция для получения информации о процессоре
void GetProcessorInfo() {
    std::cout << "Processor: " << std::endl;
    std::system("wmic cpu get name");
}

// Функция для получения информации об операционной системе
void GetOSInfo() {
    std::cout << "Operating System: " << std::endl;
    std::system("wmic os get caption, version");
}

// Функция для получения информации о звуковых устройствах
void GetAudioDevicesInfo() {
    std::cout << "Audio Devices: " << std::endl;
    std::system("wmic sounddev get caption");
}

// Функция для получения информации о USB устройствах
void GetUSBDevicesInfo() {
    std::cout << "USB Devices: " << std::endl;
    std::system("wmic path win32_pnpentity where \"PNPClass='USB'\" get caption");
}

// Функция для получения информации о сетевых адаптерах
void GetNetworkAdaptersInfo() {
    std::cout << "Network Adapters: " << std::endl;
    std::system("wmic nic get caption");
}

// Функция для получения информации о версии BIOS
void GetBIOSVersion() {
    std::cout << "BIOS Version: " << std::endl;
    std::system("wmic bios get version");
}

// Функция для получения информации о мониторах
void GetMonitorsInfo() {
    std::cout << "Monitors: " << std::endl;
    std::system("wmic desktopmonitor get caption");
}

// Функция для получения информации о видеокартах и их видеопамяти
void GetVideoCardsInfo() {
    IDXGIFactory* pFactory = NULL;
    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);

    if (pFactory) {
        std::vector<IDXGIAdapter*> adapters;
        IDXGIAdapter* pAdapter = NULL;
        for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
            adapters.push_back(pAdapter);
        }

        for (auto adapter : adapters) {
            DXGI_ADAPTER_DESC adapterDesc;
            adapter->GetDesc(&adapterDesc);
            if (wcsstr(adapterDesc.Description, L"Microsoft Basic Render Driver") == nullptr) {
                std::wcout << "Video Card: " << adapterDesc.Description << std::endl;
                std::wcout << "Video Memory: " << adapterDesc.DedicatedVideoMemory / (1024 * 1024) << " MB" << std::endl;
            }
            adapter->Release();
        }

        pFactory->Release();
    }
}

// Функция для получения информации о модулях памяти
void GetMemoryInfo() {
    std::cout << "Memory Modules: " << std::endl;

    // Получение информации о памяти через wmic и сохранение в строку
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen("wmic memorychip get capacity, speed", "r");
    if (pipe) {
        while (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
        _pclose(pipe);
    }

    // Преобразование строки и вывод значений в мегабайтах и мегагерцах
    std::istringstream iss(result);
    std::string header;
    std::getline(iss, header); // Пропускаем заголовок
    std::string line;

    // Используем set для фильтрации дубликатов
    std::unordered_set<std::string> uniqueMemoryModules;
    while (std::getline(iss, line)) {
        if (!line.empty() && uniqueMemoryModules.find(line) == uniqueMemoryModules.end()) {
            uniqueMemoryModules.insert(line);

            std::istringstream lineStream(line);
            unsigned long long capacity;
            unsigned int speed;
            lineStream >> capacity >> speed;
            if (capacity > 0) { // Проверка на валидное значение емкости
                std::cout << "Capacity: " << capacity / (1024 * 1024) << " MB, Speed: " << speed << " MHz" << std::endl;
            }
        }
    }
}

// Функция для получения информации о дисках
void GetDiskInfo() {
    std::cout << "Disk Drives: " << std::endl;
    std::system("wmic diskdrive get caption");
    std::cout << std::endl;

    std::cout << "Logical Disks: " << std::endl;
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen("wmic logicaldisk get caption, freespace, size", "r");
    if (pipe) {
        while (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
        _pclose(pipe);
    }

    // Преобразование строки и вывод значений в гигабайтах
    std::istringstream iss(result);
    std::string header;
    std::getline(iss, header); // Пропускаем заголовок
    std::string line;

    // Используем set для фильтрации дубликатов
    std::set<std::string> uniqueDisks;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            std::istringstream lineStream(line);
            std::string caption;
            unsigned long long freeSpace;
            unsigned long long size;
            lineStream >> caption >> freeSpace >> size;
            if (!caption.empty() && uniqueDisks.find(caption) == uniqueDisks.end()) {
                uniqueDisks.insert(caption);
                std::cout << "Disk: " << caption << ", Free Space: " << freeSpace / (1024 * 1024 * 1024) << " GB, Size: " << size / (1024 * 1024 * 1024) << " GB" << std::endl;
            }
        }
    }
}

// Функция для получения информации о системе
void GetSystemInfo() {
    // Получение информации о процессоре
    GetProcessorInfo();
    std::cout << std::endl;

    // Получение информации об операционной системе
    GetOSInfo();
    std::cout << std::endl;

    // Получение информации о видеокартах и их видеопамяти
    GetVideoCardsInfo();
    std::cout << std::endl;

    // Получение информации о дисках
    GetDiskInfo();
    std::cout << std::endl;

    // Информация о материнской плате
    std::cout << "Motherboard: " << std::endl;
    std::system("wmic baseboard get product");
    std::cout << std::endl;

    // Получение информации о модулях памяти
    GetMemoryInfo();
    std::cout << std::endl;

    // Получение информации о версии BIOS
    GetBIOSVersion();
    std::cout << std::endl;

    // Получение информации о мониторах
    GetMonitorsInfo();
    std::cout << std::endl;

    // Получение информации о звуковых устройствах
    GetAudioDevicesInfo();
    std::cout << std::endl;

    // Получение информации о USB устройствах
    GetUSBDevicesInfo();
    std::cout << std::endl;

    // Получение информации о сетевых адаптерах
    GetNetworkAdaptersInfo();
}

int main() {
    std::wcout << L"System Information:" << std::endl;
    GetSystemInfo();
    return 0;
}
