#include <embed>

int main() {
    constexpr static const embedded data = embed( std::string_view("bark.txt", 8 ) );
    
    static_assert(data.data()[0] == '0', "constexpr data is not proper");
    static_assert(data.source() == embedded_source::file, "embed not of the proper type");
    
    return 0;
}
