#ifndef MLKEM_H
#define MLKEM_H

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

extern "C" {
    EXPORT_API void kemKeyGen();
    EXPORT_API void kemEncaps();
    EXPORT_API void kemDecaps();
}

#endif // MLKEM_H
