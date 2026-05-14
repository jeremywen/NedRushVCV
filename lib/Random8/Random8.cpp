/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
    SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
    SampleValue * out5 = (numOutputs >= 5 && outputs[4] ? outputs[4] : this->dummyBuffer);
    SampleValue * out6 = (numOutputs >= 6 && outputs[5] ? outputs[5] : this->dummyBuffer);
    SampleValue * out7 = (numOutputs >= 7 && outputs[6] ? outputs[6] : this->dummyBuffer);
    SampleValue * out8 = (numOutputs >= 8 && outputs[7] ? outputs[7] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    this->noise_tilde_01_perform(this->signals[0], n);
    this->noise_tilde_02_perform(this->signals[1], n);
    this->latch_tilde_02_perform(this->signals[1], in1, this->signals[2], n);
    this->latch_tilde_01_perform(this->signals[0], in1, this->signals[1], n);
    this->ip_01_perform(this->signals[0], n);
    this->dspexpr_03_perform(this->signals[1], this->signals[0], this->signals[3], n);
    this->ip_02_perform(this->signals[0], n);
    this->dspexpr_06_perform(this->signals[2], this->signals[0], this->signals[1], n);
    this->ip_03_perform(this->signals[0], n);
    this->dspexpr_01_perform(this->signals[3], this->signals[0], this->signals[2], n);
    this->dspexpr_02_perform(this->signals[2], this->dspexpr_02_in2, this->dspexpr_02_in3, out1, n);
    this->ip_04_perform(this->signals[2], n);
    this->dspexpr_04_perform(this->signals[1], this->signals[2], this->signals[0], n);
    this->dspexpr_05_perform(this->signals[0], this->dspexpr_05_in2, this->dspexpr_05_in3, out5, n);
    this->noise_tilde_03_perform(this->signals[0], n);
    this->latch_tilde_03_perform(this->signals[0], in1, this->signals[2], n);
    this->noise_tilde_04_perform(this->signals[0], n);
    this->latch_tilde_04_perform(this->signals[0], in1, this->signals[1], n);
    this->ip_05_perform(this->signals[0], n);
    this->dspexpr_09_perform(this->signals[2], this->signals[0], this->signals[3], n);
    this->ip_06_perform(this->signals[0], n);
    this->dspexpr_12_perform(this->signals[1], this->signals[0], this->signals[2], n);
    this->ip_07_perform(this->signals[0], n);
    this->dspexpr_07_perform(this->signals[3], this->signals[0], this->signals[1], n);
    this->dspexpr_08_perform(this->signals[1], this->dspexpr_08_in2, this->dspexpr_08_in3, out2, n);
    this->ip_08_perform(this->signals[1], n);
    this->dspexpr_10_perform(this->signals[2], this->signals[1], this->signals[0], n);
    this->dspexpr_11_perform(this->signals[0], this->dspexpr_11_in2, this->dspexpr_11_in3, out6, n);
    this->noise_tilde_05_perform(this->signals[0], n);
    this->latch_tilde_05_perform(this->signals[0], in1, this->signals[1], n);
    this->noise_tilde_06_perform(this->signals[0], n);
    this->latch_tilde_06_perform(this->signals[0], in1, this->signals[2], n);
    this->ip_09_perform(this->signals[0], n);
    this->dspexpr_15_perform(this->signals[1], this->signals[0], this->signals[3], n);
    this->ip_10_perform(this->signals[0], n);
    this->dspexpr_18_perform(this->signals[2], this->signals[0], this->signals[1], n);
    this->ip_11_perform(this->signals[0], n);
    this->dspexpr_13_perform(this->signals[3], this->signals[0], this->signals[2], n);
    this->dspexpr_14_perform(this->signals[2], this->dspexpr_14_in2, this->dspexpr_14_in3, out3, n);
    this->ip_12_perform(this->signals[2], n);
    this->dspexpr_16_perform(this->signals[1], this->signals[2], this->signals[0], n);
    this->dspexpr_17_perform(this->signals[0], this->dspexpr_17_in2, this->dspexpr_17_in3, out7, n);
    this->noise_tilde_07_perform(this->signals[0], n);
    this->latch_tilde_07_perform(this->signals[0], in1, this->signals[2], n);
    this->noise_tilde_08_perform(this->signals[0], n);
    this->latch_tilde_08_perform(this->signals[0], in1, this->signals[1], n);
    this->ip_13_perform(this->signals[0], n);
    this->dspexpr_21_perform(this->signals[2], this->signals[0], this->signals[3], n);
    this->ip_14_perform(this->signals[0], n);
    this->dspexpr_24_perform(this->signals[1], this->signals[0], this->signals[2], n);
    this->ip_15_perform(this->signals[0], n);
    this->dspexpr_19_perform(this->signals[3], this->signals[0], this->signals[1], n);
    this->dspexpr_20_perform(this->signals[1], this->dspexpr_20_in2, this->dspexpr_20_in3, out4, n);
    this->ip_16_perform(this->signals[1], n);
    this->dspexpr_22_perform(this->signals[2], this->signals[1], this->signals[0], n);
    this->dspexpr_23_perform(this->signals[0], this->dspexpr_23_in2, this->dspexpr_23_in3, out8, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 4; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
        this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
        this->ip_03_sigbuf = resizeSignal(this->ip_03_sigbuf, this->maxvs, maxBlockSize);
        this->ip_04_sigbuf = resizeSignal(this->ip_04_sigbuf, this->maxvs, maxBlockSize);
        this->ip_05_sigbuf = resizeSignal(this->ip_05_sigbuf, this->maxvs, maxBlockSize);
        this->ip_06_sigbuf = resizeSignal(this->ip_06_sigbuf, this->maxvs, maxBlockSize);
        this->ip_07_sigbuf = resizeSignal(this->ip_07_sigbuf, this->maxvs, maxBlockSize);
        this->ip_08_sigbuf = resizeSignal(this->ip_08_sigbuf, this->maxvs, maxBlockSize);
        this->ip_09_sigbuf = resizeSignal(this->ip_09_sigbuf, this->maxvs, maxBlockSize);
        this->ip_10_sigbuf = resizeSignal(this->ip_10_sigbuf, this->maxvs, maxBlockSize);
        this->ip_11_sigbuf = resizeSignal(this->ip_11_sigbuf, this->maxvs, maxBlockSize);
        this->ip_12_sigbuf = resizeSignal(this->ip_12_sigbuf, this->maxvs, maxBlockSize);
        this->ip_13_sigbuf = resizeSignal(this->ip_13_sigbuf, this->maxvs, maxBlockSize);
        this->ip_14_sigbuf = resizeSignal(this->ip_14_sigbuf, this->maxvs, maxBlockSize);
        this->ip_15_sigbuf = resizeSignal(this->ip_15_sigbuf, this->maxvs, maxBlockSize);
        this->ip_16_sigbuf = resizeSignal(this->ip_16_sigbuf, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->noise_tilde_01_dspsetup(forceDSPSetup);
    this->noise_tilde_02_dspsetup(forceDSPSetup);
    this->latch_tilde_02_dspsetup(forceDSPSetup);
    this->latch_tilde_01_dspsetup(forceDSPSetup);
    this->ip_01_dspsetup(forceDSPSetup);
    this->ip_02_dspsetup(forceDSPSetup);
    this->ip_03_dspsetup(forceDSPSetup);
    this->ip_04_dspsetup(forceDSPSetup);
    this->noise_tilde_03_dspsetup(forceDSPSetup);
    this->latch_tilde_03_dspsetup(forceDSPSetup);
    this->noise_tilde_04_dspsetup(forceDSPSetup);
    this->latch_tilde_04_dspsetup(forceDSPSetup);
    this->ip_05_dspsetup(forceDSPSetup);
    this->ip_06_dspsetup(forceDSPSetup);
    this->ip_07_dspsetup(forceDSPSetup);
    this->ip_08_dspsetup(forceDSPSetup);
    this->noise_tilde_05_dspsetup(forceDSPSetup);
    this->latch_tilde_05_dspsetup(forceDSPSetup);
    this->noise_tilde_06_dspsetup(forceDSPSetup);
    this->latch_tilde_06_dspsetup(forceDSPSetup);
    this->ip_09_dspsetup(forceDSPSetup);
    this->ip_10_dspsetup(forceDSPSetup);
    this->ip_11_dspsetup(forceDSPSetup);
    this->ip_12_dspsetup(forceDSPSetup);
    this->noise_tilde_07_dspsetup(forceDSPSetup);
    this->latch_tilde_07_dspsetup(forceDSPSetup);
    this->noise_tilde_08_dspsetup(forceDSPSetup);
    this->latch_tilde_08_dspsetup(forceDSPSetup);
    this->ip_13_dspsetup(forceDSPSetup);
    this->ip_14_dspsetup(forceDSPSetup);
    this->ip_15_dspsetup(forceDSPSetup);
    this->ip_16_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 1;
}

Index getNumOutputChannels() const {
    return 8;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);
    this->assign_defaults();
    this->applyState();
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "1atten"));
    this->param_02_getPresetValue(getSubState(preset, "5atten"));
    this->param_03_getPresetValue(getSubState(preset, "1offset"));
    this->param_04_getPresetValue(getSubState(preset, "5offset"));
    this->param_05_getPresetValue(getSubState(preset, "2atten"));
    this->param_06_getPresetValue(getSubState(preset, "6atten"));
    this->param_07_getPresetValue(getSubState(preset, "2offset"));
    this->param_08_getPresetValue(getSubState(preset, "6offset"));
    this->param_09_getPresetValue(getSubState(preset, "3atten"));
    this->param_10_getPresetValue(getSubState(preset, "7atten"));
    this->param_11_getPresetValue(getSubState(preset, "3offset"));
    this->param_12_getPresetValue(getSubState(preset, "7offset"));
    this->param_13_getPresetValue(getSubState(preset, "4atten"));
    this->param_14_getPresetValue(getSubState(preset, "8atten"));
    this->param_15_getPresetValue(getSubState(preset, "4offset"));
    this->param_16_getPresetValue(getSubState(preset, "8offset"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->param_01_setPresetValue(getSubState(preset, "1atten"));
    this->param_02_setPresetValue(getSubState(preset, "5atten"));
    this->param_03_setPresetValue(getSubState(preset, "1offset"));
    this->param_04_setPresetValue(getSubState(preset, "5offset"));
    this->param_05_setPresetValue(getSubState(preset, "2atten"));
    this->param_06_setPresetValue(getSubState(preset, "6atten"));
    this->param_07_setPresetValue(getSubState(preset, "2offset"));
    this->param_08_setPresetValue(getSubState(preset, "6offset"));
    this->param_09_setPresetValue(getSubState(preset, "3atten"));
    this->param_10_setPresetValue(getSubState(preset, "7atten"));
    this->param_11_setPresetValue(getSubState(preset, "3offset"));
    this->param_12_setPresetValue(getSubState(preset, "7offset"));
    this->param_13_setPresetValue(getSubState(preset, "4atten"));
    this->param_14_setPresetValue(getSubState(preset, "8atten"));
    this->param_15_setPresetValue(getSubState(preset, "4offset"));
    this->param_16_setPresetValue(getSubState(preset, "8offset"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_11_value_set(v);
        break;
        }
    case 11:
        {
        this->param_12_value_set(v);
        break;
        }
    case 12:
        {
        this->param_13_value_set(v);
        break;
        }
    case 13:
        {
        this->param_14_value_set(v);
        break;
        }
    case 14:
        {
        this->param_15_value_set(v);
        break;
        }
    case 15:
        {
        this->param_16_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_11_value;
        }
    case 11:
        {
        return this->param_12_value;
        }
    case 12:
        {
        return this->param_13_value;
        }
    case 13:
        {
        return this->param_14_value;
        }
    case 14:
        {
        return this->param_15_value;
        }
    case 15:
        {
        return this->param_16_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 16;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "1atten";
        }
    case 1:
        {
        return "5atten";
        }
    case 2:
        {
        return "1offset";
        }
    case 3:
        {
        return "5offset";
        }
    case 4:
        {
        return "2atten";
        }
    case 5:
        {
        return "6atten";
        }
    case 6:
        {
        return "2offset";
        }
    case 7:
        {
        return "6offset";
        }
    case 8:
        {
        return "3atten";
        }
    case 9:
        {
        return "7atten";
        }
    case 10:
        {
        return "3offset";
        }
    case 11:
        {
        return "7offset";
        }
    case 12:
        {
        return "4atten";
        }
    case 13:
        {
        return "8atten";
        }
    case 14:
        {
        return "4offset";
        }
    case 15:
        {
        return "8offset";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "1atten";
        }
    case 1:
        {
        return "5atten";
        }
    case 2:
        {
        return "1offset";
        }
    case 3:
        {
        return "5offset";
        }
    case 4:
        {
        return "2atten";
        }
    case 5:
        {
        return "6atten";
        }
    case 6:
        {
        return "2offset";
        }
    case 7:
        {
        return "6offset";
        }
    case 8:
        {
        return "3atten";
        }
    case 9:
        {
        return "7atten";
        }
    case 10:
        {
        return "3offset";
        }
    case 11:
        {
        return "7offset";
        }
    case 12:
        {
        return "4atten";
        }
    case 13:
        {
        return "8atten";
        }
    case 14:
        {
        return "4offset";
        }
    case 15:
        {
        return "8offset";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 1:
    case 4:
    case 5:
    case 8:
    case 9:
    case 12:
    case 13:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 11:
    case 14:
    case 15:
        {
        {
            value = (value < -1 ? -1 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - -1) / (1 - -1);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
    case 4:
    case 5:
    case 8:
    case 9:
    case 12:
    case 13:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 11:
    case 14:
    case 15:
        {
        {
            {
                return -1 + value * (1 - -1);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_11_value_constrain(value);
        }
    case 11:
        {
        return this->param_12_value_constrain(value);
        }
    case 12:
        {
        return this->param_13_value_constrain(value);
        }
    case 13:
        {
        return this->param_14_value_constrain(value);
        }
    case 14:
        {
        return this->param_15_value_constrain(value);
        }
    case 15:
        {
        return this->param_16_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}

void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}

void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

Index voice() {
    return this->_voiceIndex;
}

number random(number low, number high) {
    number range = high - low;
    return globalrandom() * range + low;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_01_lastValue = this->param_01_value;
    }

    this->ip_01_value_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_02_lastValue = this->param_02_value;
    }

    this->ip_02_value_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_03_lastValue = this->param_03_value;
    }

    this->ip_03_value_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_04_lastValue = this->param_04_value;
    }

    this->ip_04_value_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_05_lastValue = this->param_05_value;
    }

    this->ip_05_value_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_06_lastValue = this->param_06_value;
    }

    this->ip_06_value_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_07_lastValue = this->param_07_value;
    }

    this->ip_07_value_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_08_lastValue = this->param_08_value;
    }

    this->ip_08_value_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_09_lastValue = this->param_09_value;
    }

    this->ip_09_value_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_10_lastValue = this->param_10_value;
    }

    this->ip_10_value_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_11_lastValue = this->param_11_value;
    }

    this->ip_11_value_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_12_lastValue = this->param_12_value;
    }

    this->ip_12_value_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_13_lastValue = this->param_13_value;
    }

    this->ip_13_value_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_14_lastValue = this->param_14_value;
    }

    this->ip_14_value_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(14, false);

    if (this->param_15_value != this->param_15_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_15_lastValue = this->param_15_value;
    }

    this->ip_15_value_set(v);
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(15, false);

    if (this->param_16_value != this->param_16_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_16_lastValue = this->param_16_value;
    }

    this->ip_16_value_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 4; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->ip_01_sigbuf = freeSignal(this->ip_01_sigbuf);
    this->ip_02_sigbuf = freeSignal(this->ip_02_sigbuf);
    this->ip_03_sigbuf = freeSignal(this->ip_03_sigbuf);
    this->ip_04_sigbuf = freeSignal(this->ip_04_sigbuf);
    this->ip_05_sigbuf = freeSignal(this->ip_05_sigbuf);
    this->ip_06_sigbuf = freeSignal(this->ip_06_sigbuf);
    this->ip_07_sigbuf = freeSignal(this->ip_07_sigbuf);
    this->ip_08_sigbuf = freeSignal(this->ip_08_sigbuf);
    this->ip_09_sigbuf = freeSignal(this->ip_09_sigbuf);
    this->ip_10_sigbuf = freeSignal(this->ip_10_sigbuf);
    this->ip_11_sigbuf = freeSignal(this->ip_11_sigbuf);
    this->ip_12_sigbuf = freeSignal(this->ip_12_sigbuf);
    this->ip_13_sigbuf = freeSignal(this->ip_13_sigbuf);
    this->ip_14_sigbuf = freeSignal(this->ip_14_sigbuf);
    this->ip_15_sigbuf = freeSignal(this->ip_15_sigbuf);
    this->ip_16_sigbuf = freeSignal(this->ip_16_sigbuf);
    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillDataRef(DataRefIndex , DataRef& ) {}

void allocateDataRefs() {}

void initializeObjects() {
    this->latch_tilde_01_init();
    this->noise_tilde_01_nz_init();
    this->latch_tilde_02_init();
    this->noise_tilde_02_nz_init();
    this->ip_01_init();
    this->ip_02_init();
    this->ip_03_init();
    this->ip_04_init();
    this->latch_tilde_03_init();
    this->noise_tilde_03_nz_init();
    this->latch_tilde_04_init();
    this->noise_tilde_04_nz_init();
    this->ip_05_init();
    this->ip_06_init();
    this->ip_07_init();
    this->ip_08_init();
    this->latch_tilde_05_init();
    this->noise_tilde_05_nz_init();
    this->latch_tilde_06_init();
    this->noise_tilde_06_nz_init();
    this->ip_09_init();
    this->ip_10_init();
    this->ip_11_init();
    this->ip_12_init();
    this->latch_tilde_07_init();
    this->noise_tilde_07_nz_init();
    this->latch_tilde_08_init();
    this->noise_tilde_08_nz_init();
    this->ip_13_init();
    this->ip_14_init();
    this->ip_15_init();
    this->ip_16_init();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_01_value_set(number v) {
    this->ip_01_value = v;
    this->ip_01_fillSigBuf();
    this->ip_01_lastValue = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_02_value_set(number v) {
    this->ip_02_value = v;
    this->ip_02_fillSigBuf();
    this->ip_02_lastValue = v;
}

number param_03_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_03_value_set(number v) {
    this->ip_03_value = v;
    this->ip_03_fillSigBuf();
    this->ip_03_lastValue = v;
}

number param_04_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_04_value_set(number v) {
    this->ip_04_value = v;
    this->ip_04_fillSigBuf();
    this->ip_04_lastValue = v;
}

number param_05_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_05_value_set(number v) {
    this->ip_05_value = v;
    this->ip_05_fillSigBuf();
    this->ip_05_lastValue = v;
}

number param_06_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_06_value_set(number v) {
    this->ip_06_value = v;
    this->ip_06_fillSigBuf();
    this->ip_06_lastValue = v;
}

number param_07_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_07_value_set(number v) {
    this->ip_07_value = v;
    this->ip_07_fillSigBuf();
    this->ip_07_lastValue = v;
}

number param_08_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_08_value_set(number v) {
    this->ip_08_value = v;
    this->ip_08_fillSigBuf();
    this->ip_08_lastValue = v;
}

number param_09_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_09_value_set(number v) {
    this->ip_09_value = v;
    this->ip_09_fillSigBuf();
    this->ip_09_lastValue = v;
}

number param_10_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_10_value_set(number v) {
    this->ip_10_value = v;
    this->ip_10_fillSigBuf();
    this->ip_10_lastValue = v;
}

number param_11_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_11_value_set(number v) {
    this->ip_11_value = v;
    this->ip_11_fillSigBuf();
    this->ip_11_lastValue = v;
}

number param_12_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_12_value_set(number v) {
    this->ip_12_value = v;
    this->ip_12_fillSigBuf();
    this->ip_12_lastValue = v;
}

number param_13_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_13_value_set(number v) {
    this->ip_13_value = v;
    this->ip_13_fillSigBuf();
    this->ip_13_lastValue = v;
}

number param_14_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void ip_14_value_set(number v) {
    this->ip_14_value = v;
    this->ip_14_fillSigBuf();
    this->ip_14_lastValue = v;
}

number param_15_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_15_value_set(number v) {
    this->ip_15_value = v;
    this->ip_15_fillSigBuf();
    this->ip_15_lastValue = v;
}

number param_16_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

void ip_16_value_set(number v) {
    this->ip_16_value = v;
    this->ip_16_fillSigBuf();
    this->ip_16_lastValue = v;
}

void noise_tilde_01_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_01_nz_next();
    }
}

void noise_tilde_02_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_02_nz_next();
    }
}

void latch_tilde_02_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_02_value = this->latch_tilde_02_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_02_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_02_value;
    }

    this->latch_tilde_02_value = __latch_tilde_02_value;
}

void latch_tilde_01_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_01_value = this->latch_tilde_01_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_01_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_01_value;
    }

    this->latch_tilde_01_value = __latch_tilde_01_value;
}

void ip_01_perform(SampleValue * out, Index n) {
    auto __ip_01_lastValue = this->ip_01_lastValue;
    auto __ip_01_lastIndex = this->ip_01_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : this->ip_01_sigbuf[(Index)i]);
    }

    __ip_01_lastIndex = 0;
    this->ip_01_lastIndex = __ip_01_lastIndex;
}

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_02_perform(SampleValue * out, Index n) {
    auto __ip_02_lastValue = this->ip_02_lastValue;
    auto __ip_02_lastIndex = this->ip_02_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_02_lastIndex ? __ip_02_lastValue : this->ip_02_sigbuf[(Index)i]);
    }

    __ip_02_lastIndex = 0;
    this->ip_02_lastIndex = __ip_02_lastIndex;
}

void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_03_perform(SampleValue * out, Index n) {
    auto __ip_03_lastValue = this->ip_03_lastValue;
    auto __ip_03_lastIndex = this->ip_03_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_03_lastIndex ? __ip_03_lastValue : this->ip_03_sigbuf[(Index)i]);
    }

    __ip_03_lastIndex = 0;
    this->ip_03_lastIndex = __ip_03_lastIndex;
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_02_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void ip_04_perform(SampleValue * out, Index n) {
    auto __ip_04_lastValue = this->ip_04_lastValue;
    auto __ip_04_lastIndex = this->ip_04_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_04_lastIndex ? __ip_04_lastValue : this->ip_04_sigbuf[(Index)i]);
    }

    __ip_04_lastIndex = 0;
    this->ip_04_lastIndex = __ip_04_lastIndex;
}

void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_05_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void noise_tilde_03_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_03_nz_next();
    }
}

void latch_tilde_03_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_03_value = this->latch_tilde_03_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_03_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_03_value;
    }

    this->latch_tilde_03_value = __latch_tilde_03_value;
}

void noise_tilde_04_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_04_nz_next();
    }
}

void latch_tilde_04_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_04_value = this->latch_tilde_04_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_04_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_04_value;
    }

    this->latch_tilde_04_value = __latch_tilde_04_value;
}

void ip_05_perform(SampleValue * out, Index n) {
    auto __ip_05_lastValue = this->ip_05_lastValue;
    auto __ip_05_lastIndex = this->ip_05_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_05_lastIndex ? __ip_05_lastValue : this->ip_05_sigbuf[(Index)i]);
    }

    __ip_05_lastIndex = 0;
    this->ip_05_lastIndex = __ip_05_lastIndex;
}

void dspexpr_09_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_06_perform(SampleValue * out, Index n) {
    auto __ip_06_lastValue = this->ip_06_lastValue;
    auto __ip_06_lastIndex = this->ip_06_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_06_lastIndex ? __ip_06_lastValue : this->ip_06_sigbuf[(Index)i]);
    }

    __ip_06_lastIndex = 0;
    this->ip_06_lastIndex = __ip_06_lastIndex;
}

void dspexpr_12_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_07_perform(SampleValue * out, Index n) {
    auto __ip_07_lastValue = this->ip_07_lastValue;
    auto __ip_07_lastIndex = this->ip_07_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_07_lastIndex ? __ip_07_lastValue : this->ip_07_sigbuf[(Index)i]);
    }

    __ip_07_lastIndex = 0;
    this->ip_07_lastIndex = __ip_07_lastIndex;
}

void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_08_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void ip_08_perform(SampleValue * out, Index n) {
    auto __ip_08_lastValue = this->ip_08_lastValue;
    auto __ip_08_lastIndex = this->ip_08_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_08_lastIndex ? __ip_08_lastValue : this->ip_08_sigbuf[(Index)i]);
    }

    __ip_08_lastIndex = 0;
    this->ip_08_lastIndex = __ip_08_lastIndex;
}

void dspexpr_10_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_11_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void noise_tilde_05_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_05_nz_next();
    }
}

void latch_tilde_05_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_05_value = this->latch_tilde_05_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_05_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_05_value;
    }

    this->latch_tilde_05_value = __latch_tilde_05_value;
}

void noise_tilde_06_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_06_nz_next();
    }
}

void latch_tilde_06_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_06_value = this->latch_tilde_06_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_06_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_06_value;
    }

    this->latch_tilde_06_value = __latch_tilde_06_value;
}

void ip_09_perform(SampleValue * out, Index n) {
    auto __ip_09_lastValue = this->ip_09_lastValue;
    auto __ip_09_lastIndex = this->ip_09_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_09_lastIndex ? __ip_09_lastValue : this->ip_09_sigbuf[(Index)i]);
    }

    __ip_09_lastIndex = 0;
    this->ip_09_lastIndex = __ip_09_lastIndex;
}

void dspexpr_15_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_10_perform(SampleValue * out, Index n) {
    auto __ip_10_lastValue = this->ip_10_lastValue;
    auto __ip_10_lastIndex = this->ip_10_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_10_lastIndex ? __ip_10_lastValue : this->ip_10_sigbuf[(Index)i]);
    }

    __ip_10_lastIndex = 0;
    this->ip_10_lastIndex = __ip_10_lastIndex;
}

void dspexpr_18_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_11_perform(SampleValue * out, Index n) {
    auto __ip_11_lastValue = this->ip_11_lastValue;
    auto __ip_11_lastIndex = this->ip_11_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_11_lastIndex ? __ip_11_lastValue : this->ip_11_sigbuf[(Index)i]);
    }

    __ip_11_lastIndex = 0;
    this->ip_11_lastIndex = __ip_11_lastIndex;
}

void dspexpr_13_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_14_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void ip_12_perform(SampleValue * out, Index n) {
    auto __ip_12_lastValue = this->ip_12_lastValue;
    auto __ip_12_lastIndex = this->ip_12_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_12_lastIndex ? __ip_12_lastValue : this->ip_12_sigbuf[(Index)i]);
    }

    __ip_12_lastIndex = 0;
    this->ip_12_lastIndex = __ip_12_lastIndex;
}

void dspexpr_16_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_17_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void noise_tilde_07_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_07_nz_next();
    }
}

void latch_tilde_07_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_07_value = this->latch_tilde_07_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_07_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_07_value;
    }

    this->latch_tilde_07_value = __latch_tilde_07_value;
}

void noise_tilde_08_perform(SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->noise_tilde_08_nz_next();
    }
}

void latch_tilde_08_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
    auto __latch_tilde_08_value = this->latch_tilde_08_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (control[(Index)i] != 0.) {
            __latch_tilde_08_value = x[(Index)i];
        }

        out1[(Index)i] = __latch_tilde_08_value;
    }

    this->latch_tilde_08_value = __latch_tilde_08_value;
}

void ip_13_perform(SampleValue * out, Index n) {
    auto __ip_13_lastValue = this->ip_13_lastValue;
    auto __ip_13_lastIndex = this->ip_13_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_13_lastIndex ? __ip_13_lastValue : this->ip_13_sigbuf[(Index)i]);
    }

    __ip_13_lastIndex = 0;
    this->ip_13_lastIndex = __ip_13_lastIndex;
}

void dspexpr_21_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_14_perform(SampleValue * out, Index n) {
    auto __ip_14_lastValue = this->ip_14_lastValue;
    auto __ip_14_lastIndex = this->ip_14_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_14_lastIndex ? __ip_14_lastValue : this->ip_14_sigbuf[(Index)i]);
    }

    __ip_14_lastIndex = 0;
    this->ip_14_lastIndex = __ip_14_lastIndex;
}

void dspexpr_24_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void ip_15_perform(SampleValue * out, Index n) {
    auto __ip_15_lastValue = this->ip_15_lastValue;
    auto __ip_15_lastIndex = this->ip_15_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_15_lastIndex ? __ip_15_lastValue : this->ip_15_sigbuf[(Index)i]);
    }

    __ip_15_lastIndex = 0;
    this->ip_15_lastIndex = __ip_15_lastIndex;
}

void dspexpr_19_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_20_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void ip_16_perform(SampleValue * out, Index n) {
    auto __ip_16_lastValue = this->ip_16_lastValue;
    auto __ip_16_lastIndex = this->ip_16_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_16_lastIndex ? __ip_16_lastValue : this->ip_16_sigbuf[(Index)i]);
    }

    __ip_16_lastIndex = 0;
    this->ip_16_lastIndex = __ip_16_lastIndex;
}

void dspexpr_22_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_23_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void latch_tilde_01_init() {
    this->latch_tilde_01_reset();
}

void latch_tilde_01_reset() {
    this->latch_tilde_01_value = 0;
}

void latch_tilde_01_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_01_reset();
    this->latch_tilde_01_setupDone = true;
}

void noise_tilde_01_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_01_nz_state
    );
}

void noise_tilde_01_nz_init() {
    this->noise_tilde_01_nz_reset();
}

void noise_tilde_01_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_01_nz_state);
}

number noise_tilde_01_nz_next() {
    return xoshiro_next(this->noise_tilde_01_nz_state);
}

void noise_tilde_01_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_01_setupDone = true;
}

void latch_tilde_02_init() {
    this->latch_tilde_02_reset();
}

void latch_tilde_02_reset() {
    this->latch_tilde_02_value = 0;
}

void latch_tilde_02_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_02_reset();
    this->latch_tilde_02_setupDone = true;
}

void noise_tilde_02_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_02_nz_state
    );
}

void noise_tilde_02_nz_init() {
    this->noise_tilde_02_nz_reset();
}

void noise_tilde_02_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_02_nz_state);
}

number noise_tilde_02_nz_next() {
    return xoshiro_next(this->noise_tilde_02_nz_state);
}

void noise_tilde_02_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_02_setupDone = true;
}

void ip_01_init() {
    this->ip_01_lastValue = this->ip_01_value;
}

void ip_01_fillSigBuf() {
    if ((bool)(this->ip_01_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_01_lastIndex); i < k; i++) {
            if (this->ip_01_resetCount > 0) {
                this->ip_01_sigbuf[(Index)i] = 1;
                this->ip_01_resetCount--;
            } else {
                this->ip_01_sigbuf[(Index)i] = this->ip_01_lastValue;
            }
        }

        this->ip_01_lastIndex = k;
    }
}

void ip_01_dspsetup(bool force) {
    if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_01_lastIndex = 0;
    this->ip_01_setupDone = true;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void ip_02_init() {
    this->ip_02_lastValue = this->ip_02_value;
}

void ip_02_fillSigBuf() {
    if ((bool)(this->ip_02_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_02_lastIndex); i < k; i++) {
            if (this->ip_02_resetCount > 0) {
                this->ip_02_sigbuf[(Index)i] = 1;
                this->ip_02_resetCount--;
            } else {
                this->ip_02_sigbuf[(Index)i] = this->ip_02_lastValue;
            }
        }

        this->ip_02_lastIndex = k;
    }
}

void ip_02_dspsetup(bool force) {
    if ((bool)(this->ip_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_02_lastIndex = 0;
    this->ip_02_setupDone = true;
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void ip_03_init() {
    this->ip_03_lastValue = this->ip_03_value;
}

void ip_03_fillSigBuf() {
    if ((bool)(this->ip_03_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_03_lastIndex); i < k; i++) {
            if (this->ip_03_resetCount > 0) {
                this->ip_03_sigbuf[(Index)i] = 1;
                this->ip_03_resetCount--;
            } else {
                this->ip_03_sigbuf[(Index)i] = this->ip_03_lastValue;
            }
        }

        this->ip_03_lastIndex = k;
    }
}

void ip_03_dspsetup(bool force) {
    if ((bool)(this->ip_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_03_lastIndex = 0;
    this->ip_03_setupDone = true;
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void ip_04_init() {
    this->ip_04_lastValue = this->ip_04_value;
}

void ip_04_fillSigBuf() {
    if ((bool)(this->ip_04_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_04_lastIndex); i < k; i++) {
            if (this->ip_04_resetCount > 0) {
                this->ip_04_sigbuf[(Index)i] = 1;
                this->ip_04_resetCount--;
            } else {
                this->ip_04_sigbuf[(Index)i] = this->ip_04_lastValue;
            }
        }

        this->ip_04_lastIndex = k;
    }
}

void ip_04_dspsetup(bool force) {
    if ((bool)(this->ip_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_04_lastIndex = 0;
    this->ip_04_setupDone = true;
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void latch_tilde_03_init() {
    this->latch_tilde_03_reset();
}

void latch_tilde_03_reset() {
    this->latch_tilde_03_value = 0;
}

void latch_tilde_03_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_03_reset();
    this->latch_tilde_03_setupDone = true;
}

void noise_tilde_03_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_03_nz_state
    );
}

void noise_tilde_03_nz_init() {
    this->noise_tilde_03_nz_reset();
}

void noise_tilde_03_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_03_nz_state);
}

number noise_tilde_03_nz_next() {
    return xoshiro_next(this->noise_tilde_03_nz_state);
}

void noise_tilde_03_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_03_setupDone = true;
}

void latch_tilde_04_init() {
    this->latch_tilde_04_reset();
}

void latch_tilde_04_reset() {
    this->latch_tilde_04_value = 0;
}

void latch_tilde_04_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_04_reset();
    this->latch_tilde_04_setupDone = true;
}

void noise_tilde_04_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_04_nz_state
    );
}

void noise_tilde_04_nz_init() {
    this->noise_tilde_04_nz_reset();
}

void noise_tilde_04_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_04_nz_state);
}

number noise_tilde_04_nz_next() {
    return xoshiro_next(this->noise_tilde_04_nz_state);
}

void noise_tilde_04_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_04_setupDone = true;
}

void ip_05_init() {
    this->ip_05_lastValue = this->ip_05_value;
}

void ip_05_fillSigBuf() {
    if ((bool)(this->ip_05_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_05_lastIndex); i < k; i++) {
            if (this->ip_05_resetCount > 0) {
                this->ip_05_sigbuf[(Index)i] = 1;
                this->ip_05_resetCount--;
            } else {
                this->ip_05_sigbuf[(Index)i] = this->ip_05_lastValue;
            }
        }

        this->ip_05_lastIndex = k;
    }
}

void ip_05_dspsetup(bool force) {
    if ((bool)(this->ip_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_05_lastIndex = 0;
    this->ip_05_setupDone = true;
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void ip_06_init() {
    this->ip_06_lastValue = this->ip_06_value;
}

void ip_06_fillSigBuf() {
    if ((bool)(this->ip_06_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_06_lastIndex); i < k; i++) {
            if (this->ip_06_resetCount > 0) {
                this->ip_06_sigbuf[(Index)i] = 1;
                this->ip_06_resetCount--;
            } else {
                this->ip_06_sigbuf[(Index)i] = this->ip_06_lastValue;
            }
        }

        this->ip_06_lastIndex = k;
    }
}

void ip_06_dspsetup(bool force) {
    if ((bool)(this->ip_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_06_lastIndex = 0;
    this->ip_06_setupDone = true;
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void ip_07_init() {
    this->ip_07_lastValue = this->ip_07_value;
}

void ip_07_fillSigBuf() {
    if ((bool)(this->ip_07_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_07_lastIndex); i < k; i++) {
            if (this->ip_07_resetCount > 0) {
                this->ip_07_sigbuf[(Index)i] = 1;
                this->ip_07_resetCount--;
            } else {
                this->ip_07_sigbuf[(Index)i] = this->ip_07_lastValue;
            }
        }

        this->ip_07_lastIndex = k;
    }
}

void ip_07_dspsetup(bool force) {
    if ((bool)(this->ip_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_07_lastIndex = 0;
    this->ip_07_setupDone = true;
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void ip_08_init() {
    this->ip_08_lastValue = this->ip_08_value;
}

void ip_08_fillSigBuf() {
    if ((bool)(this->ip_08_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_08_lastIndex); i < k; i++) {
            if (this->ip_08_resetCount > 0) {
                this->ip_08_sigbuf[(Index)i] = 1;
                this->ip_08_resetCount--;
            } else {
                this->ip_08_sigbuf[(Index)i] = this->ip_08_lastValue;
            }
        }

        this->ip_08_lastIndex = k;
    }
}

void ip_08_dspsetup(bool force) {
    if ((bool)(this->ip_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_08_lastIndex = 0;
    this->ip_08_setupDone = true;
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void latch_tilde_05_init() {
    this->latch_tilde_05_reset();
}

void latch_tilde_05_reset() {
    this->latch_tilde_05_value = 0;
}

void latch_tilde_05_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_05_reset();
    this->latch_tilde_05_setupDone = true;
}

void noise_tilde_05_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_05_nz_state
    );
}

void noise_tilde_05_nz_init() {
    this->noise_tilde_05_nz_reset();
}

void noise_tilde_05_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_05_nz_state);
}

number noise_tilde_05_nz_next() {
    return xoshiro_next(this->noise_tilde_05_nz_state);
}

void noise_tilde_05_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_05_setupDone = true;
}

void latch_tilde_06_init() {
    this->latch_tilde_06_reset();
}

void latch_tilde_06_reset() {
    this->latch_tilde_06_value = 0;
}

void latch_tilde_06_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_06_reset();
    this->latch_tilde_06_setupDone = true;
}

void noise_tilde_06_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_06_nz_state
    );
}

void noise_tilde_06_nz_init() {
    this->noise_tilde_06_nz_reset();
}

void noise_tilde_06_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_06_nz_state);
}

number noise_tilde_06_nz_next() {
    return xoshiro_next(this->noise_tilde_06_nz_state);
}

void noise_tilde_06_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_06_setupDone = true;
}

void ip_09_init() {
    this->ip_09_lastValue = this->ip_09_value;
}

void ip_09_fillSigBuf() {
    if ((bool)(this->ip_09_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_09_lastIndex); i < k; i++) {
            if (this->ip_09_resetCount > 0) {
                this->ip_09_sigbuf[(Index)i] = 1;
                this->ip_09_resetCount--;
            } else {
                this->ip_09_sigbuf[(Index)i] = this->ip_09_lastValue;
            }
        }

        this->ip_09_lastIndex = k;
    }
}

void ip_09_dspsetup(bool force) {
    if ((bool)(this->ip_09_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_09_lastIndex = 0;
    this->ip_09_setupDone = true;
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void ip_10_init() {
    this->ip_10_lastValue = this->ip_10_value;
}

void ip_10_fillSigBuf() {
    if ((bool)(this->ip_10_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_10_lastIndex); i < k; i++) {
            if (this->ip_10_resetCount > 0) {
                this->ip_10_sigbuf[(Index)i] = 1;
                this->ip_10_resetCount--;
            } else {
                this->ip_10_sigbuf[(Index)i] = this->ip_10_lastValue;
            }
        }

        this->ip_10_lastIndex = k;
    }
}

void ip_10_dspsetup(bool force) {
    if ((bool)(this->ip_10_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_10_lastIndex = 0;
    this->ip_10_setupDone = true;
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void ip_11_init() {
    this->ip_11_lastValue = this->ip_11_value;
}

void ip_11_fillSigBuf() {
    if ((bool)(this->ip_11_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_11_lastIndex); i < k; i++) {
            if (this->ip_11_resetCount > 0) {
                this->ip_11_sigbuf[(Index)i] = 1;
                this->ip_11_resetCount--;
            } else {
                this->ip_11_sigbuf[(Index)i] = this->ip_11_lastValue;
            }
        }

        this->ip_11_lastIndex = k;
    }
}

void ip_11_dspsetup(bool force) {
    if ((bool)(this->ip_11_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_11_lastIndex = 0;
    this->ip_11_setupDone = true;
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void ip_12_init() {
    this->ip_12_lastValue = this->ip_12_value;
}

void ip_12_fillSigBuf() {
    if ((bool)(this->ip_12_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_12_lastIndex); i < k; i++) {
            if (this->ip_12_resetCount > 0) {
                this->ip_12_sigbuf[(Index)i] = 1;
                this->ip_12_resetCount--;
            } else {
                this->ip_12_sigbuf[(Index)i] = this->ip_12_lastValue;
            }
        }

        this->ip_12_lastIndex = k;
    }
}

void ip_12_dspsetup(bool force) {
    if ((bool)(this->ip_12_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_12_lastIndex = 0;
    this->ip_12_setupDone = true;
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void latch_tilde_07_init() {
    this->latch_tilde_07_reset();
}

void latch_tilde_07_reset() {
    this->latch_tilde_07_value = 0;
}

void latch_tilde_07_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_07_reset();
    this->latch_tilde_07_setupDone = true;
}

void noise_tilde_07_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_07_nz_state
    );
}

void noise_tilde_07_nz_init() {
    this->noise_tilde_07_nz_reset();
}

void noise_tilde_07_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_07_nz_state);
}

number noise_tilde_07_nz_next() {
    return xoshiro_next(this->noise_tilde_07_nz_state);
}

void noise_tilde_07_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_07_setupDone = true;
}

void latch_tilde_08_init() {
    this->latch_tilde_08_reset();
}

void latch_tilde_08_reset() {
    this->latch_tilde_08_value = 0;
}

void latch_tilde_08_dspsetup(bool force) {
    if ((bool)(this->latch_tilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->latch_tilde_08_reset();
    this->latch_tilde_08_setupDone = true;
}

void noise_tilde_08_nz_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->noise_tilde_08_nz_state
    );
}

void noise_tilde_08_nz_init() {
    this->noise_tilde_08_nz_reset();
}

void noise_tilde_08_nz_seed(number v) {
    xoshiro_reset(v, this->noise_tilde_08_nz_state);
}

number noise_tilde_08_nz_next() {
    return xoshiro_next(this->noise_tilde_08_nz_state);
}

void noise_tilde_08_dspsetup(bool force) {
    if ((bool)(this->noise_tilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->noise_tilde_08_setupDone = true;
}

void ip_13_init() {
    this->ip_13_lastValue = this->ip_13_value;
}

void ip_13_fillSigBuf() {
    if ((bool)(this->ip_13_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_13_lastIndex); i < k; i++) {
            if (this->ip_13_resetCount > 0) {
                this->ip_13_sigbuf[(Index)i] = 1;
                this->ip_13_resetCount--;
            } else {
                this->ip_13_sigbuf[(Index)i] = this->ip_13_lastValue;
            }
        }

        this->ip_13_lastIndex = k;
    }
}

void ip_13_dspsetup(bool force) {
    if ((bool)(this->ip_13_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_13_lastIndex = 0;
    this->ip_13_setupDone = true;
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void ip_14_init() {
    this->ip_14_lastValue = this->ip_14_value;
}

void ip_14_fillSigBuf() {
    if ((bool)(this->ip_14_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_14_lastIndex); i < k; i++) {
            if (this->ip_14_resetCount > 0) {
                this->ip_14_sigbuf[(Index)i] = 1;
                this->ip_14_resetCount--;
            } else {
                this->ip_14_sigbuf[(Index)i] = this->ip_14_lastValue;
            }
        }

        this->ip_14_lastIndex = k;
    }
}

void ip_14_dspsetup(bool force) {
    if ((bool)(this->ip_14_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_14_lastIndex = 0;
    this->ip_14_setupDone = true;
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void ip_15_init() {
    this->ip_15_lastValue = this->ip_15_value;
}

void ip_15_fillSigBuf() {
    if ((bool)(this->ip_15_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_15_lastIndex); i < k; i++) {
            if (this->ip_15_resetCount > 0) {
                this->ip_15_sigbuf[(Index)i] = 1;
                this->ip_15_resetCount--;
            } else {
                this->ip_15_sigbuf[(Index)i] = this->ip_15_lastValue;
            }
        }

        this->ip_15_lastIndex = k;
    }
}

void ip_15_dspsetup(bool force) {
    if ((bool)(this->ip_15_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_15_lastIndex = 0;
    this->ip_15_setupDone = true;
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

void ip_16_init() {
    this->ip_16_lastValue = this->ip_16_value;
}

void ip_16_fillSigBuf() {
    if ((bool)(this->ip_16_sigbuf)) {
        SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);

        if (k >= (SampleIndex)(this->vs))
            k = (SampleIndex)(this->vs) - 1;

        for (SampleIndex i = (SampleIndex)(this->ip_16_lastIndex); i < k; i++) {
            if (this->ip_16_resetCount > 0) {
                this->ip_16_sigbuf[(Index)i] = 1;
                this->ip_16_resetCount--;
            } else {
                this->ip_16_sigbuf[(Index)i] = this->ip_16_lastValue;
            }
        }

        this->ip_16_lastIndex = k;
    }
}

void ip_16_dspsetup(bool force) {
    if ((bool)(this->ip_16_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_16_lastIndex = 0;
    this->ip_16_setupDone = true;
}

void param_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_16_value;
}

void param_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_16_value_set(preset["value"]);
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = -1;
    dspexpr_02_in3 = 1;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 1;
    latch_tilde_01_x = 0;
    latch_tilde_01_control = 0;
    noise_tilde_01_seed = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = -1;
    dspexpr_05_in3 = 1;
    dspexpr_06_in1 = 0;
    dspexpr_06_in2 = 1;
    latch_tilde_02_x = 0;
    latch_tilde_02_control = 0;
    noise_tilde_02_seed = 0;
    ip_01_value = 0;
    ip_01_impulse = 0;
    param_01_value = 1;
    ip_02_value = 0;
    ip_02_impulse = 0;
    param_02_value = 1;
    ip_03_value = 0;
    ip_03_impulse = 0;
    param_03_value = 0;
    ip_04_value = 0;
    ip_04_impulse = 0;
    param_04_value = 0;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    dspexpr_08_in1 = 0;
    dspexpr_08_in2 = -1;
    dspexpr_08_in3 = 1;
    dspexpr_09_in1 = 0;
    dspexpr_09_in2 = 1;
    latch_tilde_03_x = 0;
    latch_tilde_03_control = 0;
    noise_tilde_03_seed = 0;
    dspexpr_10_in1 = 0;
    dspexpr_10_in2 = 0;
    dspexpr_11_in1 = 0;
    dspexpr_11_in2 = -1;
    dspexpr_11_in3 = 1;
    dspexpr_12_in1 = 0;
    dspexpr_12_in2 = 1;
    latch_tilde_04_x = 0;
    latch_tilde_04_control = 0;
    noise_tilde_04_seed = 0;
    ip_05_value = 0;
    ip_05_impulse = 0;
    param_05_value = 1;
    ip_06_value = 0;
    ip_06_impulse = 0;
    param_06_value = 1;
    ip_07_value = 0;
    ip_07_impulse = 0;
    param_07_value = 0;
    ip_08_value = 0;
    ip_08_impulse = 0;
    param_08_value = 0;
    dspexpr_13_in1 = 0;
    dspexpr_13_in2 = 0;
    dspexpr_14_in1 = 0;
    dspexpr_14_in2 = -1;
    dspexpr_14_in3 = 1;
    dspexpr_15_in1 = 0;
    dspexpr_15_in2 = 1;
    latch_tilde_05_x = 0;
    latch_tilde_05_control = 0;
    noise_tilde_05_seed = 0;
    dspexpr_16_in1 = 0;
    dspexpr_16_in2 = 0;
    dspexpr_17_in1 = 0;
    dspexpr_17_in2 = -1;
    dspexpr_17_in3 = 1;
    dspexpr_18_in1 = 0;
    dspexpr_18_in2 = 1;
    latch_tilde_06_x = 0;
    latch_tilde_06_control = 0;
    noise_tilde_06_seed = 0;
    ip_09_value = 0;
    ip_09_impulse = 0;
    param_09_value = 1;
    ip_10_value = 0;
    ip_10_impulse = 0;
    param_10_value = 1;
    ip_11_value = 0;
    ip_11_impulse = 0;
    param_11_value = 0;
    ip_12_value = 0;
    ip_12_impulse = 0;
    param_12_value = 0;
    dspexpr_19_in1 = 0;
    dspexpr_19_in2 = 0;
    dspexpr_20_in1 = 0;
    dspexpr_20_in2 = -1;
    dspexpr_20_in3 = 1;
    dspexpr_21_in1 = 0;
    dspexpr_21_in2 = 1;
    latch_tilde_07_x = 0;
    latch_tilde_07_control = 0;
    noise_tilde_07_seed = 0;
    dspexpr_22_in1 = 0;
    dspexpr_22_in2 = 0;
    dspexpr_23_in1 = 0;
    dspexpr_23_in2 = -1;
    dspexpr_23_in3 = 1;
    dspexpr_24_in1 = 0;
    dspexpr_24_in2 = 1;
    latch_tilde_08_x = 0;
    latch_tilde_08_control = 0;
    noise_tilde_08_seed = 0;
    ip_13_value = 0;
    ip_13_impulse = 0;
    param_13_value = 1;
    ip_14_value = 0;
    ip_14_impulse = 0;
    param_14_value = 1;
    ip_15_value = 0;
    ip_15_impulse = 0;
    param_15_value = 0;
    ip_16_value = 0;
    ip_16_impulse = 0;
    param_16_value = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    latch_tilde_01_value = 0;
    latch_tilde_01_setupDone = false;
    noise_tilde_01_setupDone = false;
    latch_tilde_02_value = 0;
    latch_tilde_02_setupDone = false;
    noise_tilde_02_setupDone = false;
    ip_01_lastIndex = 0;
    ip_01_lastValue = 0;
    ip_01_resetCount = 0;
    ip_01_sigbuf = nullptr;
    ip_01_setupDone = false;
    param_01_lastValue = 0;
    ip_02_lastIndex = 0;
    ip_02_lastValue = 0;
    ip_02_resetCount = 0;
    ip_02_sigbuf = nullptr;
    ip_02_setupDone = false;
    param_02_lastValue = 0;
    ip_03_lastIndex = 0;
    ip_03_lastValue = 0;
    ip_03_resetCount = 0;
    ip_03_sigbuf = nullptr;
    ip_03_setupDone = false;
    param_03_lastValue = 0;
    ip_04_lastIndex = 0;
    ip_04_lastValue = 0;
    ip_04_resetCount = 0;
    ip_04_sigbuf = nullptr;
    ip_04_setupDone = false;
    param_04_lastValue = 0;
    latch_tilde_03_value = 0;
    latch_tilde_03_setupDone = false;
    noise_tilde_03_setupDone = false;
    latch_tilde_04_value = 0;
    latch_tilde_04_setupDone = false;
    noise_tilde_04_setupDone = false;
    ip_05_lastIndex = 0;
    ip_05_lastValue = 0;
    ip_05_resetCount = 0;
    ip_05_sigbuf = nullptr;
    ip_05_setupDone = false;
    param_05_lastValue = 0;
    ip_06_lastIndex = 0;
    ip_06_lastValue = 0;
    ip_06_resetCount = 0;
    ip_06_sigbuf = nullptr;
    ip_06_setupDone = false;
    param_06_lastValue = 0;
    ip_07_lastIndex = 0;
    ip_07_lastValue = 0;
    ip_07_resetCount = 0;
    ip_07_sigbuf = nullptr;
    ip_07_setupDone = false;
    param_07_lastValue = 0;
    ip_08_lastIndex = 0;
    ip_08_lastValue = 0;
    ip_08_resetCount = 0;
    ip_08_sigbuf = nullptr;
    ip_08_setupDone = false;
    param_08_lastValue = 0;
    latch_tilde_05_value = 0;
    latch_tilde_05_setupDone = false;
    noise_tilde_05_setupDone = false;
    latch_tilde_06_value = 0;
    latch_tilde_06_setupDone = false;
    noise_tilde_06_setupDone = false;
    ip_09_lastIndex = 0;
    ip_09_lastValue = 0;
    ip_09_resetCount = 0;
    ip_09_sigbuf = nullptr;
    ip_09_setupDone = false;
    param_09_lastValue = 0;
    ip_10_lastIndex = 0;
    ip_10_lastValue = 0;
    ip_10_resetCount = 0;
    ip_10_sigbuf = nullptr;
    ip_10_setupDone = false;
    param_10_lastValue = 0;
    ip_11_lastIndex = 0;
    ip_11_lastValue = 0;
    ip_11_resetCount = 0;
    ip_11_sigbuf = nullptr;
    ip_11_setupDone = false;
    param_11_lastValue = 0;
    ip_12_lastIndex = 0;
    ip_12_lastValue = 0;
    ip_12_resetCount = 0;
    ip_12_sigbuf = nullptr;
    ip_12_setupDone = false;
    param_12_lastValue = 0;
    latch_tilde_07_value = 0;
    latch_tilde_07_setupDone = false;
    noise_tilde_07_setupDone = false;
    latch_tilde_08_value = 0;
    latch_tilde_08_setupDone = false;
    noise_tilde_08_setupDone = false;
    ip_13_lastIndex = 0;
    ip_13_lastValue = 0;
    ip_13_resetCount = 0;
    ip_13_sigbuf = nullptr;
    ip_13_setupDone = false;
    param_13_lastValue = 0;
    ip_14_lastIndex = 0;
    ip_14_lastValue = 0;
    ip_14_resetCount = 0;
    ip_14_sigbuf = nullptr;
    ip_14_setupDone = false;
    param_14_lastValue = 0;
    ip_15_lastIndex = 0;
    ip_15_lastValue = 0;
    ip_15_resetCount = 0;
    ip_15_sigbuf = nullptr;
    ip_15_setupDone = false;
    param_15_lastValue = 0;
    ip_16_lastIndex = 0;
    ip_16_lastValue = 0;
    ip_16_resetCount = 0;
    ip_16_sigbuf = nullptr;
    ip_16_setupDone = false;
    param_16_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number dspexpr_02_in3;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number latch_tilde_01_x;
    number latch_tilde_01_control;
    number noise_tilde_01_seed;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number dspexpr_05_in3;
    number dspexpr_06_in1;
    number dspexpr_06_in2;
    number latch_tilde_02_x;
    number latch_tilde_02_control;
    number noise_tilde_02_seed;
    number ip_01_value;
    number ip_01_impulse;
    number param_01_value;
    number ip_02_value;
    number ip_02_impulse;
    number param_02_value;
    number ip_03_value;
    number ip_03_impulse;
    number param_03_value;
    number ip_04_value;
    number ip_04_impulse;
    number param_04_value;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number dspexpr_08_in1;
    number dspexpr_08_in2;
    number dspexpr_08_in3;
    number dspexpr_09_in1;
    number dspexpr_09_in2;
    number latch_tilde_03_x;
    number latch_tilde_03_control;
    number noise_tilde_03_seed;
    number dspexpr_10_in1;
    number dspexpr_10_in2;
    number dspexpr_11_in1;
    number dspexpr_11_in2;
    number dspexpr_11_in3;
    number dspexpr_12_in1;
    number dspexpr_12_in2;
    number latch_tilde_04_x;
    number latch_tilde_04_control;
    number noise_tilde_04_seed;
    number ip_05_value;
    number ip_05_impulse;
    number param_05_value;
    number ip_06_value;
    number ip_06_impulse;
    number param_06_value;
    number ip_07_value;
    number ip_07_impulse;
    number param_07_value;
    number ip_08_value;
    number ip_08_impulse;
    number param_08_value;
    number dspexpr_13_in1;
    number dspexpr_13_in2;
    number dspexpr_14_in1;
    number dspexpr_14_in2;
    number dspexpr_14_in3;
    number dspexpr_15_in1;
    number dspexpr_15_in2;
    number latch_tilde_05_x;
    number latch_tilde_05_control;
    number noise_tilde_05_seed;
    number dspexpr_16_in1;
    number dspexpr_16_in2;
    number dspexpr_17_in1;
    number dspexpr_17_in2;
    number dspexpr_17_in3;
    number dspexpr_18_in1;
    number dspexpr_18_in2;
    number latch_tilde_06_x;
    number latch_tilde_06_control;
    number noise_tilde_06_seed;
    number ip_09_value;
    number ip_09_impulse;
    number param_09_value;
    number ip_10_value;
    number ip_10_impulse;
    number param_10_value;
    number ip_11_value;
    number ip_11_impulse;
    number param_11_value;
    number ip_12_value;
    number ip_12_impulse;
    number param_12_value;
    number dspexpr_19_in1;
    number dspexpr_19_in2;
    number dspexpr_20_in1;
    number dspexpr_20_in2;
    number dspexpr_20_in3;
    number dspexpr_21_in1;
    number dspexpr_21_in2;
    number latch_tilde_07_x;
    number latch_tilde_07_control;
    number noise_tilde_07_seed;
    number dspexpr_22_in1;
    number dspexpr_22_in2;
    number dspexpr_23_in1;
    number dspexpr_23_in2;
    number dspexpr_23_in3;
    number dspexpr_24_in1;
    number dspexpr_24_in2;
    number latch_tilde_08_x;
    number latch_tilde_08_control;
    number noise_tilde_08_seed;
    number ip_13_value;
    number ip_13_impulse;
    number param_13_value;
    number ip_14_value;
    number ip_14_impulse;
    number param_14_value;
    number ip_15_value;
    number ip_15_impulse;
    number param_15_value;
    number ip_16_value;
    number ip_16_impulse;
    number param_16_value;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[4];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number latch_tilde_01_value;
    bool latch_tilde_01_setupDone;
    UInt noise_tilde_01_nz_state[4] = { };
    bool noise_tilde_01_setupDone;
    number latch_tilde_02_value;
    bool latch_tilde_02_setupDone;
    UInt noise_tilde_02_nz_state[4] = { };
    bool noise_tilde_02_setupDone;
    SampleIndex ip_01_lastIndex;
    number ip_01_lastValue;
    SampleIndex ip_01_resetCount;
    signal ip_01_sigbuf;
    bool ip_01_setupDone;
    number param_01_lastValue;
    SampleIndex ip_02_lastIndex;
    number ip_02_lastValue;
    SampleIndex ip_02_resetCount;
    signal ip_02_sigbuf;
    bool ip_02_setupDone;
    number param_02_lastValue;
    SampleIndex ip_03_lastIndex;
    number ip_03_lastValue;
    SampleIndex ip_03_resetCount;
    signal ip_03_sigbuf;
    bool ip_03_setupDone;
    number param_03_lastValue;
    SampleIndex ip_04_lastIndex;
    number ip_04_lastValue;
    SampleIndex ip_04_resetCount;
    signal ip_04_sigbuf;
    bool ip_04_setupDone;
    number param_04_lastValue;
    number latch_tilde_03_value;
    bool latch_tilde_03_setupDone;
    UInt noise_tilde_03_nz_state[4] = { };
    bool noise_tilde_03_setupDone;
    number latch_tilde_04_value;
    bool latch_tilde_04_setupDone;
    UInt noise_tilde_04_nz_state[4] = { };
    bool noise_tilde_04_setupDone;
    SampleIndex ip_05_lastIndex;
    number ip_05_lastValue;
    SampleIndex ip_05_resetCount;
    signal ip_05_sigbuf;
    bool ip_05_setupDone;
    number param_05_lastValue;
    SampleIndex ip_06_lastIndex;
    number ip_06_lastValue;
    SampleIndex ip_06_resetCount;
    signal ip_06_sigbuf;
    bool ip_06_setupDone;
    number param_06_lastValue;
    SampleIndex ip_07_lastIndex;
    number ip_07_lastValue;
    SampleIndex ip_07_resetCount;
    signal ip_07_sigbuf;
    bool ip_07_setupDone;
    number param_07_lastValue;
    SampleIndex ip_08_lastIndex;
    number ip_08_lastValue;
    SampleIndex ip_08_resetCount;
    signal ip_08_sigbuf;
    bool ip_08_setupDone;
    number param_08_lastValue;
    number latch_tilde_05_value;
    bool latch_tilde_05_setupDone;
    UInt noise_tilde_05_nz_state[4] = { };
    bool noise_tilde_05_setupDone;
    number latch_tilde_06_value;
    bool latch_tilde_06_setupDone;
    UInt noise_tilde_06_nz_state[4] = { };
    bool noise_tilde_06_setupDone;
    SampleIndex ip_09_lastIndex;
    number ip_09_lastValue;
    SampleIndex ip_09_resetCount;
    signal ip_09_sigbuf;
    bool ip_09_setupDone;
    number param_09_lastValue;
    SampleIndex ip_10_lastIndex;
    number ip_10_lastValue;
    SampleIndex ip_10_resetCount;
    signal ip_10_sigbuf;
    bool ip_10_setupDone;
    number param_10_lastValue;
    SampleIndex ip_11_lastIndex;
    number ip_11_lastValue;
    SampleIndex ip_11_resetCount;
    signal ip_11_sigbuf;
    bool ip_11_setupDone;
    number param_11_lastValue;
    SampleIndex ip_12_lastIndex;
    number ip_12_lastValue;
    SampleIndex ip_12_resetCount;
    signal ip_12_sigbuf;
    bool ip_12_setupDone;
    number param_12_lastValue;
    number latch_tilde_07_value;
    bool latch_tilde_07_setupDone;
    UInt noise_tilde_07_nz_state[4] = { };
    bool noise_tilde_07_setupDone;
    number latch_tilde_08_value;
    bool latch_tilde_08_setupDone;
    UInt noise_tilde_08_nz_state[4] = { };
    bool noise_tilde_08_setupDone;
    SampleIndex ip_13_lastIndex;
    number ip_13_lastValue;
    SampleIndex ip_13_resetCount;
    signal ip_13_sigbuf;
    bool ip_13_setupDone;
    number param_13_lastValue;
    SampleIndex ip_14_lastIndex;
    number ip_14_lastValue;
    SampleIndex ip_14_resetCount;
    signal ip_14_sigbuf;
    bool ip_14_setupDone;
    number param_14_lastValue;
    SampleIndex ip_15_lastIndex;
    number ip_15_lastValue;
    SampleIndex ip_15_resetCount;
    signal ip_15_sigbuf;
    bool ip_15_setupDone;
    number param_15_lastValue;
    SampleIndex ip_16_lastIndex;
    number ip_16_lastValue;
    SampleIndex ip_16_resetCount;
    signal ip_16_sigbuf;
    bool ip_16_setupDone;
    number param_16_lastValue;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

