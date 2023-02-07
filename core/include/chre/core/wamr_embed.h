#ifndef CHRE_PLATFORM_WAMR_EMBED_H_
#define CHRE_PLATFORM_WAMR_EMBED_H_
namespace chre {
class WebAssemblyMicroRuntime {
public:
    static bool init();
    static void deinit();
};
}
#endif