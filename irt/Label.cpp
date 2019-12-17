#include "Label.h"

namespace IrTree {

    std::unordered_map<std::wstring, int> IrtLabel::labelCounters;
    std::unordered_map<std::wstring, int> IrtTemp::tempCounters;

    IrtLabel::IrtLabel(const std::wstring& _label) {
        if (labelCounters.find(_label) == labelCounters.end() ) {
            labelCounters[_label] = 0;
        }
        label = L"Label_" + _label + L"_" + std::to_wstring(labelCounters[_label]++);
    }

    IrtTemp::IrtTemp(const std::wstring& _label) {
        if (tempCounters.find(_label) == tempCounters.end() ) {
            tempCounters[_label] = 0;
        }
        label = L"Temp_" + _label + L"_" + std::to_wstring(tempCounters[_label]++);
    }
}