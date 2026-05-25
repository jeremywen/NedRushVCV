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
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
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
    SampleValue * out9 = (numOutputs >= 9 && outputs[8] ? outputs[8] : this->dummyBuffer);
    this->phasor_01_perform(this->phasor_01_freq, this->signals[0], n);
    this->subdivobject_08_perform(this->signals[0], this->signals[1], this->dummyBuffer, n);
    this->delta_tilde_09_perform(this->signals[1], this->signals[2], n);
    this->dspexpr_09_perform(this->signals[2], this->dspexpr_09_in2, out9, n);
    this->subdivobject_07_perform(this->signals[0], this->signals[2], this->dummyBuffer, n);
    this->delta_tilde_08_perform(this->signals[2], this->signals[1], n);
    this->dspexpr_08_perform(this->signals[1], this->dspexpr_08_in2, out8, n);
    this->subdivobject_06_perform(this->signals[0], this->signals[1], this->dummyBuffer, n);
    this->delta_tilde_07_perform(this->signals[1], this->signals[2], n);
    this->dspexpr_07_perform(this->signals[2], this->dspexpr_07_in2, out7, n);
    this->subdivobject_05_perform(this->signals[0], this->signals[2], this->dummyBuffer, n);
    this->delta_tilde_06_perform(this->signals[2], this->signals[1], n);
    this->dspexpr_06_perform(this->signals[1], this->dspexpr_06_in2, out6, n);
    this->subdivobject_04_perform(this->signals[0], this->signals[1], this->dummyBuffer, n);
    this->delta_tilde_05_perform(this->signals[1], this->signals[2], n);
    this->dspexpr_05_perform(this->signals[2], this->dspexpr_05_in2, out5, n);
    this->subdivobject_03_perform(this->signals[0], this->signals[2], this->dummyBuffer, n);
    this->delta_tilde_04_perform(this->signals[2], this->signals[1], n);
    this->dspexpr_04_perform(this->signals[1], this->dspexpr_04_in2, out4, n);
    this->subdivobject_02_perform(this->signals[0], this->signals[1], this->dummyBuffer, n);
    this->delta_tilde_03_perform(this->signals[1], this->signals[2], n);
    this->dspexpr_03_perform(this->signals[2], this->dspexpr_03_in2, out3, n);
    this->subdivobject_01_perform(this->signals[0], this->signals[2], this->dummyBuffer, n);
    this->delta_tilde_02_perform(this->signals[2], this->signals[1], n);
    this->dspexpr_02_perform(this->signals[1], this->dspexpr_02_in2, out2, n);
    this->delta_tilde_01_perform(this->signals[0], this->signals[1], n);
    this->dspexpr_01_perform(this->signals[1], this->dspexpr_01_in2, out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 3; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
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

    this->subdivobject_08_dspsetup(forceDSPSetup);
    this->delta_tilde_09_dspsetup(forceDSPSetup);
    this->subdivobject_07_dspsetup(forceDSPSetup);
    this->delta_tilde_08_dspsetup(forceDSPSetup);
    this->subdivobject_06_dspsetup(forceDSPSetup);
    this->delta_tilde_07_dspsetup(forceDSPSetup);
    this->subdivobject_05_dspsetup(forceDSPSetup);
    this->delta_tilde_06_dspsetup(forceDSPSetup);
    this->subdivobject_04_dspsetup(forceDSPSetup);
    this->delta_tilde_05_dspsetup(forceDSPSetup);
    this->subdivobject_03_dspsetup(forceDSPSetup);
    this->delta_tilde_04_dspsetup(forceDSPSetup);
    this->subdivobject_02_dspsetup(forceDSPSetup);
    this->delta_tilde_03_dspsetup(forceDSPSetup);
    this->subdivobject_01_dspsetup(forceDSPSetup);
    this->delta_tilde_02_dspsetup(forceDSPSetup);
    this->delta_tilde_01_dspsetup(forceDSPSetup);
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
    return 0;
}

Index getNumOutputChannels() const {
    return 9;
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

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->transport_01_onTempoChanged(tempo);
        this->timevalue_01_onTempoChanged(tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->transport_01_onTransportChanged(state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->phasor_01_onBeatTimeChanged(beattime);
    }
}

void processTimeSignatureEvent(MillisecondTime time, Int numerator, Int denominator) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->transport_01_onTimeSignatureChanged(numerator, denominator);
        this->timevalue_01_onTimeSignatureChanged(numerator, denominator);
    }
}

void processBBUEvent(MillisecondTime time, number bars, number beats, number units) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBBU(this->_currentTime, bars, beats, units, false))
        {}
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "startstop"));
    this->param_02_getPresetValue(getSubState(preset, "div1"));
    this->param_03_getPresetValue(getSubState(preset, "div2"));
    this->param_04_getPresetValue(getSubState(preset, "tempo"));
    this->param_05_getPresetValue(getSubState(preset, "div3"));
    this->param_06_getPresetValue(getSubState(preset, "div4"));
    this->param_07_getPresetValue(getSubState(preset, "div5"));
    this->param_08_getPresetValue(getSubState(preset, "div6"));
    this->param_09_getPresetValue(getSubState(preset, "div7"));
    this->param_10_getPresetValue(getSubState(preset, "div8"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->param_01_setPresetValue(getSubState(preset, "startstop"));
    this->param_02_setPresetValue(getSubState(preset, "div1"));
    this->param_03_setPresetValue(getSubState(preset, "div2"));
    this->param_04_setPresetValue(getSubState(preset, "tempo"));
    this->param_05_setPresetValue(getSubState(preset, "div3"));
    this->param_06_setPresetValue(getSubState(preset, "div4"));
    this->param_07_setPresetValue(getSubState(preset, "div5"));
    this->param_08_setPresetValue(getSubState(preset, "div6"));
    this->param_09_setPresetValue(getSubState(preset, "div7"));
    this->param_10_setPresetValue(getSubState(preset, "div8"));
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
    return 10;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "startstop";
        }
    case 1:
        {
        return "div1";
        }
    case 2:
        {
        return "div2";
        }
    case 3:
        {
        return "tempo";
        }
    case 4:
        {
        return "div3";
        }
    case 5:
        {
        return "div4";
        }
    case 6:
        {
        return "div5";
        }
    case 7:
        {
        return "div6";
        }
    case 8:
        {
        return "div7";
        }
    case 9:
        {
        return "div8";
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
        return "startstop";
        }
    case 1:
        {
        return "div1";
        }
    case 2:
        {
        return "div2";
        }
    case 3:
        {
        return "tempo";
        }
    case 4:
        {
        return "div3";
        }
    case 5:
        {
        return "div4";
        }
    case 6:
        {
        return "div5";
        }
    case 7:
        {
        return "div6";
        }
    case 8:
        {
        return "div7";
        }
    case 9:
        {
        return "div8";
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal0[] = {"0", "1"};
            info->enumValues = eVal0;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal1[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal1;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal2[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal2;
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
            info->initialValue = 120;
            info->min = 1;
            info->max = 999;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal4[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal4;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal5[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal5;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal6[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal6;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal7[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal7;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal8[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal8;
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
            info->initialValue = 15;
            info->min = 0;
            info->max = 15;
            info->exponent = 1;
            info->steps = 16;

            static const char * eVal9[] = {
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "10",
                "11",
                "12",
                "13",
                "14",
                "15",
                "16"
            };

            info->enumValues = eVal9;
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
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 15 ? 15 : value));
            ParameterValue normalizedValue = (value - 0) / (15 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 16);
            }

            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 1 ? 1 : (value > 999 ? 999 : value));
            ParameterValue normalizedValue = (value - 1) / (999 - 1);
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
        {
        {
            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        {
        {
            {
                value = this->applyStepsToNormalizedParameterValue(value, 16);
            }

            {
                return 0 + value * (15 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return 1 + value * (999 - 1);
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
    getEngine()->flushClockEvents(this, -972091856, false);
    getEngine()->flushClockEvents(this, -1835586767, false);
    getEngine()->flushClockEvents(this, 1595885618, false);
    getEngine()->flushClockEvents(this, 732390707, false);
    getEngine()->flushClockEvents(this, -131104204, false);
    getEngine()->flushClockEvents(this, -994599115, false);
    getEngine()->flushClockEvents(this, -1858094026, false);
    getEngine()->flushClockEvents(this, 1573378359, false);
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

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->_currentTime);
}

number hztobeats(number hz) {
    return this->safediv(this->tempo() * 8, hz * 480.);
}

number transportatsample(SampleIndex sampleOffset) {
    return this->getTopLevelPatcher()->globaltransport_getStateAtSample(sampleOffset);
}

number beattimeatsample(number offset) {
    return this->getTopLevelPatcher()->globaltransport_getBeatTimeAtSample(offset);
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

template<typename LISTTYPE = list> array<ListNum, 2> listcompare(const LISTTYPE& input1, const LISTTYPE& input2) {
    array<ListNum, 2> tmp = {};
    tmp[0] = 0;
    tmp[1] = {};
    list longList = (input1->length >= input2->length ? input1 : input2);
    list shortList = (input2->length <= input1->length ? input2 : input1);

    for (Index i = 0; i < shortList->length; i++) {
        if (longList[(Index)i] != shortList[(Index)i])
            tmp[1]->push(i);
    }

    for (Index i = (Index)(shortList->length); i < longList->length; i++) {
        tmp[1]->push(i);
    }

    if (tmp[1]->length > 0) {
        tmp[0] = 0;
    } else {
        tmp[0] = 1;
    }

    return tmp;
}

number random(number low, number high) {
    number range = high - low;
    return globalrandom() * range + low;
}

array<number, 2> timesignature() {
    return this->getTopLevelPatcher()->globaltransport_getTimeSignature(this->_currentTime);
}

number tickstohz(number ticks) {
    return (number)1 / (ticks / (number)480 * this->safediv(60, this->tempo()));
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

    this->transport_01_input_number_set(v);
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

    this->subdivobject_01_input_number_set(v);
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

    this->subdivobject_02_input_number_set(v);
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

    this->transport_01_tempo_set(v);
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

    this->subdivobject_03_input_number_set(v);
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

    this->subdivobject_04_input_number_set(v);
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

    this->subdivobject_05_input_number_set(v);
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

    this->subdivobject_06_input_number_set(v);
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

    this->subdivobject_07_input_number_set(v);
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

    this->subdivobject_08_input_number_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void subdivobject_01_stepmessage_set(number v) {
    this->subdivobject_01_stepmessage = v;
}

void subdivobject_02_stepmessage_set(number v) {
    this->subdivobject_02_stepmessage = v;
}

void subdivobject_03_stepmessage_set(number v) {
    this->subdivobject_03_stepmessage = v;
}

void subdivobject_04_stepmessage_set(number v) {
    this->subdivobject_04_stepmessage = v;
}

void subdivobject_05_stepmessage_set(number v) {
    this->subdivobject_05_stepmessage = v;
}

void subdivobject_06_stepmessage_set(number v) {
    this->subdivobject_06_stepmessage = v;
}

void subdivobject_07_stepmessage_set(number v) {
    this->subdivobject_07_stepmessage = v;
}

void subdivobject_08_stepmessage_set(number v) {
    this->subdivobject_08_stepmessage = v;
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 3; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->phasor_01_sigbuf = freeSignal(this->phasor_01_sigbuf);
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
    this->subdivobject_01_subdivider_init();
    this->subdivobject_02_subdivider_init();
    this->subdivobject_03_subdivider_init();
    this->subdivobject_04_subdivider_init();
    this->subdivobject_05_subdivider_init();
    this->subdivobject_06_subdivider_init();
    this->subdivobject_07_subdivider_init();
    this->subdivobject_08_subdivider_init();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double samplerate) {
    this->timevalue_01_onSampleRateChanged(samplerate);
}

void extractState(PatcherStateInterface& ) {}

void applyState() {}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case -972091856:
        {
        this->subdivobject_01_stepmessage_set(value);
        break;
        }
    case -1835586767:
        {
        this->subdivobject_02_stepmessage_set(value);
        break;
        }
    case 1595885618:
        {
        this->subdivobject_03_stepmessage_set(value);
        break;
        }
    case 732390707:
        {
        this->subdivobject_04_stepmessage_set(value);
        break;
        }
    case -131104204:
        {
        this->subdivobject_05_stepmessage_set(value);
        break;
        }
    case -994599115:
        {
        this->subdivobject_06_stepmessage_set(value);
        break;
        }
    case -1858094026:
        {
        this->subdivobject_07_stepmessage_set(value);
        break;
        }
    case 1573378359:
        {
        this->subdivobject_08_stepmessage_set(value);
        break;
        }
    }
}

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
    this->timevalue_01_sendValue();

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

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void transport_01_input_number_set(number v) {
    this->transport_01_input_number = v;
    this->getTopLevelPatcher()->globaltransport_setState(this->_currentTime, (v == 0 ? 0 : 1), true);
}

number param_02_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_01_div_set(number v) {
    this->subdivobject_01_div = v;
}

void subdivobject_01_input_number_set(number v) {
    this->subdivobject_01_input_number = v;
    this->subdivobject_01_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_03_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_02_div_set(number v) {
    this->subdivobject_02_div = v;
}

void subdivobject_02_input_number_set(number v) {
    this->subdivobject_02_input_number = v;
    this->subdivobject_02_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_04_value_constrain(number v) const {
    v = (v > 999 ? 999 : (v < 1 ? 1 : v));
    return v;
}

void transport_01_tempo_set(number v) {
    this->transport_01_tempo = v;

    if (v >= 0) {
        this->getTopLevelPatcher()->globaltransport_setTempo(this->_currentTime, v, true);
    }
}

number param_05_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_03_div_set(number v) {
    this->subdivobject_03_div = v;
}

void subdivobject_03_input_number_set(number v) {
    this->subdivobject_03_input_number = v;
    this->subdivobject_03_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_06_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_04_div_set(number v) {
    this->subdivobject_04_div = v;
}

void subdivobject_04_input_number_set(number v) {
    this->subdivobject_04_input_number = v;
    this->subdivobject_04_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_07_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_05_div_set(number v) {
    this->subdivobject_05_div = v;
}

void subdivobject_05_input_number_set(number v) {
    this->subdivobject_05_input_number = v;
    this->subdivobject_05_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_08_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_06_div_set(number v) {
    this->subdivobject_06_div = v;
}

void subdivobject_06_input_number_set(number v) {
    this->subdivobject_06_input_number = v;
    this->subdivobject_06_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_09_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_07_div_set(number v) {
    this->subdivobject_07_div = v;
}

void subdivobject_07_input_number_set(number v) {
    this->subdivobject_07_input_number = v;
    this->subdivobject_07_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

number param_10_value_constrain(number v) const {
    v = (v > 15 ? 15 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)15 / (number)15;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void subdivobject_08_div_set(number v) {
    this->subdivobject_08_div = v;
}

void subdivobject_08_input_number_set(number v) {
    this->subdivobject_08_input_number = v;
    this->subdivobject_08_div_set((v > 16384 ? 16384 : (v < 1 ? 1 : v)));
}

void phasor_01_freq_set(number v) {
    this->phasor_01_freq = v;
}

void timevalue_01_out_set(number v) {
    this->phasor_01_freq_set(v);
}

void transport_01_outtempo_set(number ) {}

void transport_01_state_set(number ) {}

template<typename LISTTYPE> void transport_01_outtimesig_set(const LISTTYPE& ) {}

void phasor_01_perform(number freq, SampleValue * out, Index n) {
    auto __phasor_01_lastTempo = this->phasor_01_lastTempo;
    auto __phasor_01_lastQuantum = this->phasor_01_lastQuantum;
    auto quantum = this->hztobeats(freq);

    if (quantum != __phasor_01_lastQuantum) {
        this->phasor_01_recalcInc = true;
        __phasor_01_lastQuantum = quantum;
    }

    auto tempo = this->tempo();

    if (tempo != __phasor_01_lastTempo) {
        this->phasor_01_recalcInc = true;
        __phasor_01_lastTempo = tempo;
    }

    if (quantum > 0 && tempo > 0) {
        for (Index i = 0; i < n; i++) {
            if ((bool)(this->transportatsample(i))) {
                if ((bool)(this->phasor_01_recalcInc)) {
                    this->phasor_01_recalc(quantum, this->beattimeatsample(i), tempo);
                }

                if (this->phasor_01_nextJumpInSamples <= 0) {
                    this->phasor_01_lastLockedPhase = 0;
                    this->phasor_01_recalcInc = true;
                } else {
                    this->phasor_01_lastLockedPhase += this->phasor_01_inc;
                    this->phasor_01_nextJumpInSamples--;
                }
            } else {
                this->phasor_01_recalcInc = true;
                this->phasor_01_recalcPhase = true;
            }

            out[(Index)i] = this->phasor_01_lastLockedPhase;
        }
    } else {
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = 0;
        }

        this->phasor_01_recalcInc = true;
    }

    this->phasor_01_lastQuantum = __phasor_01_lastQuantum;
    this->phasor_01_lastTempo = __phasor_01_lastTempo;
}

void subdivobject_08_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_08_silentmode = this->subdivobject_08_silentmode;
    auto __subdivobject_08_lockprob = this->subdivobject_08_lockprob;
    auto __subdivobject_08_syncupdate = this->subdivobject_08_syncupdate;
    auto __subdivobject_08_div = this->subdivobject_08_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_08_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_08_div,
            __subdivobject_08_syncupdate,
            __subdivobject_08_lockprob,
            __subdivobject_08_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        1573378359,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_09_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_09_prev = this->delta_tilde_09_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_09_prev);
        __delta_tilde_09_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_09_prev = __delta_tilde_09_prev;
}

void dspexpr_09_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_07_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_07_silentmode = this->subdivobject_07_silentmode;
    auto __subdivobject_07_lockprob = this->subdivobject_07_lockprob;
    auto __subdivobject_07_syncupdate = this->subdivobject_07_syncupdate;
    auto __subdivobject_07_div = this->subdivobject_07_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_07_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_07_div,
            __subdivobject_07_syncupdate,
            __subdivobject_07_lockprob,
            __subdivobject_07_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        -1858094026,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_08_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_08_prev = this->delta_tilde_08_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_08_prev);
        __delta_tilde_08_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_08_prev = __delta_tilde_08_prev;
}

void dspexpr_08_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_06_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_06_silentmode = this->subdivobject_06_silentmode;
    auto __subdivobject_06_lockprob = this->subdivobject_06_lockprob;
    auto __subdivobject_06_syncupdate = this->subdivobject_06_syncupdate;
    auto __subdivobject_06_div = this->subdivobject_06_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_06_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_06_div,
            __subdivobject_06_syncupdate,
            __subdivobject_06_lockprob,
            __subdivobject_06_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        -994599115,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_07_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_07_prev = this->delta_tilde_07_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_07_prev);
        __delta_tilde_07_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_07_prev = __delta_tilde_07_prev;
}

void dspexpr_07_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_05_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_05_silentmode = this->subdivobject_05_silentmode;
    auto __subdivobject_05_lockprob = this->subdivobject_05_lockprob;
    auto __subdivobject_05_syncupdate = this->subdivobject_05_syncupdate;
    auto __subdivobject_05_div = this->subdivobject_05_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_05_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_05_div,
            __subdivobject_05_syncupdate,
            __subdivobject_05_lockprob,
            __subdivobject_05_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        -131104204,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_06_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_06_prev = this->delta_tilde_06_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_06_prev);
        __delta_tilde_06_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_06_prev = __delta_tilde_06_prev;
}

void dspexpr_06_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_04_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_04_silentmode = this->subdivobject_04_silentmode;
    auto __subdivobject_04_lockprob = this->subdivobject_04_lockprob;
    auto __subdivobject_04_syncupdate = this->subdivobject_04_syncupdate;
    auto __subdivobject_04_div = this->subdivobject_04_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_04_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_04_div,
            __subdivobject_04_syncupdate,
            __subdivobject_04_lockprob,
            __subdivobject_04_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        732390707,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_05_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_05_prev = this->delta_tilde_05_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_05_prev);
        __delta_tilde_05_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_05_prev = __delta_tilde_05_prev;
}

void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_03_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_03_silentmode = this->subdivobject_03_silentmode;
    auto __subdivobject_03_lockprob = this->subdivobject_03_lockprob;
    auto __subdivobject_03_syncupdate = this->subdivobject_03_syncupdate;
    auto __subdivobject_03_div = this->subdivobject_03_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_03_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_03_div,
            __subdivobject_03_syncupdate,
            __subdivobject_03_lockprob,
            __subdivobject_03_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        1595885618,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_04_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_04_prev = this->delta_tilde_04_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_04_prev);
        __delta_tilde_04_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_04_prev = __delta_tilde_04_prev;
}

void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_02_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_02_silentmode = this->subdivobject_02_silentmode;
    auto __subdivobject_02_lockprob = this->subdivobject_02_lockprob;
    auto __subdivobject_02_syncupdate = this->subdivobject_02_syncupdate;
    auto __subdivobject_02_div = this->subdivobject_02_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_02_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_02_div,
            __subdivobject_02_syncupdate,
            __subdivobject_02_lockprob,
            __subdivobject_02_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        -1835586767,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_03_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_03_prev = this->delta_tilde_03_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_03_prev);
        __delta_tilde_03_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_03_prev = __delta_tilde_03_prev;
}

void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void subdivobject_01_perform(
    const SampleValue * input_signal,
    SampleValue * output,
    SampleValue * step,
    Index n
) {
    auto __subdivobject_01_silentmode = this->subdivobject_01_silentmode;
    auto __subdivobject_01_lockprob = this->subdivobject_01_lockprob;
    auto __subdivobject_01_syncupdate = this->subdivobject_01_syncupdate;
    auto __subdivobject_01_div = this->subdivobject_01_div;
    number stepvalue = 0;

    for (Index i = 0; i < n; i++) {
        array<number, 2> result = this->subdivobject_01_subdivider_next(
            input_signal[(Index)i],
            __subdivobject_01_div,
            __subdivobject_01_syncupdate,
            __subdivobject_01_lockprob,
            __subdivobject_01_silentmode
        );

        stepvalue = result[1];
        output[(Index)i] = result[0];
        step[(Index)i] = stepvalue;
    }

    this->getEngine()->scheduleClockEventWithValue(
        this,
        -972091856,
        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
        stepvalue
    );;
}

void delta_tilde_02_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_02_prev = this->delta_tilde_02_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_02_prev);
        __delta_tilde_02_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_02_prev = __delta_tilde_02_prev;
}

void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void delta_tilde_01_perform(const Sample * x, SampleValue * out1, Index n) {
    auto __delta_tilde_01_prev = this->delta_tilde_01_prev;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number temp = (number)(x[(Index)i] - __delta_tilde_01_prev);
        __delta_tilde_01_prev = x[(Index)i];
        out1[(Index)i] = temp;
    }

    this->delta_tilde_01_prev = __delta_tilde_01_prev;
}

void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] < 0;//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void delta_tilde_01_reset() {
    this->delta_tilde_01_prev = 0;
}

void delta_tilde_01_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_01_reset();
    this->delta_tilde_01_setupDone = true;
}

void phasor_01_onBeatTimeChanged(number beattime) {
    RNBO_UNUSED(beattime);
    this->phasor_01_recalcInc = true;
    this->phasor_01_recalcPhase = true;
}

void phasor_01_recalc(number quantum, number beattime, number tempo) {
    number samplerate = this->sr;
    number offset = fmod(beattime, quantum);
    number nextJump = quantum - offset;

    if ((bool)(this->phasor_01_recalcPhase)) {
        number oneoverquantum = (number)1 / quantum;
        this->phasor_01_lastLockedPhase = offset * oneoverquantum;
        this->phasor_01_recalcPhase = false;
    }

    this->phasor_01_nextJumpInSamples = rnbo_fround(nextJump * 60 * samplerate / tempo * 1 / (number)1) * 1;
    this->phasor_01_inc = (1 - this->phasor_01_lastLockedPhase) / (this->phasor_01_nextJumpInSamples - 1);
    this->phasor_01_recalcInc = false;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void transport_01_onTempoChanged(number state) {
    this->transport_01_outtempo_set(state);
}

void transport_01_onTransportChanged(number state) {
    this->transport_01_state_set(state);
}

void transport_01_onTimeSignatureChanged(number numerator, number denominator) {
    this->transport_01_outtimesig_set(listbase<number, 2>{numerator, denominator});
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void subdivobject_01_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_01_subdivider_pattern->length == 0) {
        this->subdivobject_01_subdivider_p2length = 0;
        this->subdivobject_01_subdivider_patternstep = 0;
        this->subdivobject_01_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_01_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_01_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_01_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_01_subdivider_div - i));

    if (this->subdivobject_01_subdivider_p2length != totalsteps) {
        this->subdivobject_01_subdivider_p2length = totalsteps;
    }

    this->subdivobject_01_subdivider_p2 = {};
    this->subdivobject_01_subdivider_synco = {};
    this->subdivobject_01_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_01_subdivider_p2->push(1);
        this->subdivobject_01_subdivider_synco->push(0);
        this->subdivobject_01_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_01_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_01_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_01_subdivider_div));
        number pv;

        if (this->subdivobject_01_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_01_subdivider_prob->length));
            pv = this->subdivobject_01_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_01_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_01_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_01_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_01_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_01_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_01_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_01_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_01_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_01_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_01_subdivider_prob->length));
                pv = this->subdivobject_01_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_01_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_01_subdivider_reset() {
    this->subdivobject_01_subdivider_outstep = 0;
    this->subdivobject_01_subdivider_posstep = 0;
    this->subdivobject_01_subdivider_probstep = 0;
    this->subdivobject_01_subdivider_lastoutstep = 0;
    this->subdivobject_01_subdivider_div = 1;
    this->subdivobject_01_subdivider_nextdiv = 1;
    this->subdivobject_01_subdivider_resolveSync();
    this->subdivobject_01_subdivider_playing = this->subdivobject_01_subdivider_isPlaying(0);
    this->subdivobject_01_subdivider_patternstep = 0;
}

void subdivobject_01_subdivider_dspsetup() {
    this->subdivobject_01_subdivider_reset();
    this->subdivobject_01_subdivider_rebuild();
}

void subdivobject_01_subdivider_init() {
    this->subdivobject_01_subdivider_reset();
    this->subdivobject_01_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_01_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_01_subdivider_prob, prob)[0]))) {
        this->subdivobject_01_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_01_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_01_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_01_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_01_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_01_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_01_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_01_subdivider_div ? this->subdivobject_01_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_01_subdivider_patternstep = 0;
        this->subdivobject_01_subdivider_rebuild();
    }
}

void subdivobject_01_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_01_subdivider_nextdiv) {
        this->subdivobject_01_subdivider_nextdiv = div;
    }
}

number subdivobject_01_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_01_subdivider_p2[(Index)(this->subdivobject_01_subdivider_patternstep + step)]);
    this->subdivobject_01_subdivider_patternphase = this->subdivobject_01_subdivider_synco[(Index)(this->subdivobject_01_subdivider_patternstep + step)];

    if (step == this->subdivobject_01_subdivider_div - 1) {
        if (this->subdivobject_01_subdivider_patternstep + this->subdivobject_01_subdivider_div >= this->subdivobject_01_subdivider_p2length) {
            this->subdivobject_01_subdivider_patternstep = 0;
        } else {
            this->subdivobject_01_subdivider_patternstep += this->subdivobject_01_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_01_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_01_subdivider_p2prob[(Index)(this->subdivobject_01_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_01_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_01_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_01_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_01_subdivider_probstep);

        if (ps >= this->subdivobject_01_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_01_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_01_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_01_subdivider_getPatternProbability(step, this->subdivobject_01_subdivider_playing);
        }

        this->subdivobject_01_subdivider_num = this->subdivobject_01_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_01_subdivider_num = 1;

        if ((bool)(this->subdivobject_01_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_01_subdivider_prob->length));
            pv = this->subdivobject_01_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_01_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_01_subdivider_resolveSync() {
    if (this->subdivobject_01_subdivider_nextdiv != this->subdivobject_01_subdivider_div) {
        this->subdivobject_01_subdivider_div = this->subdivobject_01_subdivider_nextdiv;

        if (this->subdivobject_01_subdivider_pattern->length > 0) {
            this->subdivobject_01_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_01_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_01_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_01_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_01_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_01_subdivider_div);

    if (this->subdivobject_01_subdivider_posstep >= div) {
        this->subdivobject_01_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_01_subdivider_detectReset(
        val,
        this->subdivobject_01_subdivider_prev,
        this->subdivobject_01_subdivider_prev2
    ))) {
        this->subdivobject_01_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_01_subdivider_resolveSync();
            div = this->subdivobject_01_subdivider_div;
        }

        if ((bool)(this->subdivobject_01_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_01_subdivider_lockprob))) {
            if (this->subdivobject_01_subdivider_probstep >= this->subdivobject_01_subdivider_prob->length) {
                this->subdivobject_01_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_01_subdivider_playing = this->subdivobject_01_subdivider_isPlaying(this->subdivobject_01_subdivider_posstep);
    }

    this->subdivobject_01_subdivider_prev2 = this->subdivobject_01_subdivider_prev;
    this->subdivobject_01_subdivider_prev = val;
    val *= div;
    this->subdivobject_01_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_01_subdivider_patternphase;
    val /= this->subdivobject_01_subdivider_num;
    this->subdivobject_01_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_01_subdivider_nextoutstep != this->subdivobject_01_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_01_subdivider_resolveSync();
            div = this->subdivobject_01_subdivider_div;
        }

        this->subdivobject_01_subdivider_outstep = this->subdivobject_01_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_01_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_01_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_01_subdivider_probstep += 1;

            if (this->subdivobject_01_subdivider_probstep >= this->subdivobject_01_subdivider_prob->length) {
                this->subdivobject_01_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_01_subdivider_nextposstep != this->subdivobject_01_subdivider_posstep) {
        this->subdivobject_01_subdivider_posstep = this->subdivobject_01_subdivider_nextposstep;
        this->subdivobject_01_subdivider_playing = this->subdivobject_01_subdivider_isPlaying(this->subdivobject_01_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_01_subdivider_playing)) {
        out1 = val - this->subdivobject_01_subdivider_nextoutstep;
        out2 = this->subdivobject_01_subdivider_nextoutstep;
        this->subdivobject_01_subdivider_lastoutstep = this->subdivobject_01_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_01_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_01_dspsetup(bool force) {
    if ((bool)(this->subdivobject_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_01_setupDone = true;
    this->subdivobject_01_subdivider_dspsetup();
}

void delta_tilde_02_reset() {
    this->delta_tilde_02_prev = 0;
}

void delta_tilde_02_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_02_reset();
    this->delta_tilde_02_setupDone = true;
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void subdivobject_02_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_02_subdivider_pattern->length == 0) {
        this->subdivobject_02_subdivider_p2length = 0;
        this->subdivobject_02_subdivider_patternstep = 0;
        this->subdivobject_02_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_02_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_02_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_02_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_02_subdivider_div - i));

    if (this->subdivobject_02_subdivider_p2length != totalsteps) {
        this->subdivobject_02_subdivider_p2length = totalsteps;
    }

    this->subdivobject_02_subdivider_p2 = {};
    this->subdivobject_02_subdivider_synco = {};
    this->subdivobject_02_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_02_subdivider_p2->push(1);
        this->subdivobject_02_subdivider_synco->push(0);
        this->subdivobject_02_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_02_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_02_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_02_subdivider_div));
        number pv;

        if (this->subdivobject_02_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_02_subdivider_prob->length));
            pv = this->subdivobject_02_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_02_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_02_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_02_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_02_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_02_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_02_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_02_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_02_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_02_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_02_subdivider_prob->length));
                pv = this->subdivobject_02_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_02_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_02_subdivider_reset() {
    this->subdivobject_02_subdivider_outstep = 0;
    this->subdivobject_02_subdivider_posstep = 0;
    this->subdivobject_02_subdivider_probstep = 0;
    this->subdivobject_02_subdivider_lastoutstep = 0;
    this->subdivobject_02_subdivider_div = 1;
    this->subdivobject_02_subdivider_nextdiv = 1;
    this->subdivobject_02_subdivider_resolveSync();
    this->subdivobject_02_subdivider_playing = this->subdivobject_02_subdivider_isPlaying(0);
    this->subdivobject_02_subdivider_patternstep = 0;
}

void subdivobject_02_subdivider_dspsetup() {
    this->subdivobject_02_subdivider_reset();
    this->subdivobject_02_subdivider_rebuild();
}

void subdivobject_02_subdivider_init() {
    this->subdivobject_02_subdivider_reset();
    this->subdivobject_02_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_02_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_02_subdivider_prob, prob)[0]))) {
        this->subdivobject_02_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_02_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_02_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_02_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_02_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_02_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_02_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_02_subdivider_div ? this->subdivobject_02_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_02_subdivider_patternstep = 0;
        this->subdivobject_02_subdivider_rebuild();
    }
}

void subdivobject_02_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_02_subdivider_nextdiv) {
        this->subdivobject_02_subdivider_nextdiv = div;
    }
}

number subdivobject_02_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_02_subdivider_p2[(Index)(this->subdivobject_02_subdivider_patternstep + step)]);
    this->subdivobject_02_subdivider_patternphase = this->subdivobject_02_subdivider_synco[(Index)(this->subdivobject_02_subdivider_patternstep + step)];

    if (step == this->subdivobject_02_subdivider_div - 1) {
        if (this->subdivobject_02_subdivider_patternstep + this->subdivobject_02_subdivider_div >= this->subdivobject_02_subdivider_p2length) {
            this->subdivobject_02_subdivider_patternstep = 0;
        } else {
            this->subdivobject_02_subdivider_patternstep += this->subdivobject_02_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_02_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_02_subdivider_p2prob[(Index)(this->subdivobject_02_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_02_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_02_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_02_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_02_subdivider_probstep);

        if (ps >= this->subdivobject_02_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_02_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_02_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_02_subdivider_getPatternProbability(step, this->subdivobject_02_subdivider_playing);
        }

        this->subdivobject_02_subdivider_num = this->subdivobject_02_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_02_subdivider_num = 1;

        if ((bool)(this->subdivobject_02_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_02_subdivider_prob->length));
            pv = this->subdivobject_02_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_02_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_02_subdivider_resolveSync() {
    if (this->subdivobject_02_subdivider_nextdiv != this->subdivobject_02_subdivider_div) {
        this->subdivobject_02_subdivider_div = this->subdivobject_02_subdivider_nextdiv;

        if (this->subdivobject_02_subdivider_pattern->length > 0) {
            this->subdivobject_02_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_02_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_02_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_02_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_02_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_02_subdivider_div);

    if (this->subdivobject_02_subdivider_posstep >= div) {
        this->subdivobject_02_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_02_subdivider_detectReset(
        val,
        this->subdivobject_02_subdivider_prev,
        this->subdivobject_02_subdivider_prev2
    ))) {
        this->subdivobject_02_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_02_subdivider_resolveSync();
            div = this->subdivobject_02_subdivider_div;
        }

        if ((bool)(this->subdivobject_02_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_02_subdivider_lockprob))) {
            if (this->subdivobject_02_subdivider_probstep >= this->subdivobject_02_subdivider_prob->length) {
                this->subdivobject_02_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_02_subdivider_playing = this->subdivobject_02_subdivider_isPlaying(this->subdivobject_02_subdivider_posstep);
    }

    this->subdivobject_02_subdivider_prev2 = this->subdivobject_02_subdivider_prev;
    this->subdivobject_02_subdivider_prev = val;
    val *= div;
    this->subdivobject_02_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_02_subdivider_patternphase;
    val /= this->subdivobject_02_subdivider_num;
    this->subdivobject_02_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_02_subdivider_nextoutstep != this->subdivobject_02_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_02_subdivider_resolveSync();
            div = this->subdivobject_02_subdivider_div;
        }

        this->subdivobject_02_subdivider_outstep = this->subdivobject_02_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_02_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_02_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_02_subdivider_probstep += 1;

            if (this->subdivobject_02_subdivider_probstep >= this->subdivobject_02_subdivider_prob->length) {
                this->subdivobject_02_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_02_subdivider_nextposstep != this->subdivobject_02_subdivider_posstep) {
        this->subdivobject_02_subdivider_posstep = this->subdivobject_02_subdivider_nextposstep;
        this->subdivobject_02_subdivider_playing = this->subdivobject_02_subdivider_isPlaying(this->subdivobject_02_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_02_subdivider_playing)) {
        out1 = val - this->subdivobject_02_subdivider_nextoutstep;
        out2 = this->subdivobject_02_subdivider_nextoutstep;
        this->subdivobject_02_subdivider_lastoutstep = this->subdivobject_02_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_02_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_02_dspsetup(bool force) {
    if ((bool)(this->subdivobject_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_02_setupDone = true;
    this->subdivobject_02_subdivider_dspsetup();
}

void delta_tilde_03_reset() {
    this->delta_tilde_03_prev = 0;
}

void delta_tilde_03_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_03_reset();
    this->delta_tilde_03_setupDone = true;
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void subdivobject_03_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_03_subdivider_pattern->length == 0) {
        this->subdivobject_03_subdivider_p2length = 0;
        this->subdivobject_03_subdivider_patternstep = 0;
        this->subdivobject_03_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_03_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_03_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_03_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_03_subdivider_div - i));

    if (this->subdivobject_03_subdivider_p2length != totalsteps) {
        this->subdivobject_03_subdivider_p2length = totalsteps;
    }

    this->subdivobject_03_subdivider_p2 = {};
    this->subdivobject_03_subdivider_synco = {};
    this->subdivobject_03_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_03_subdivider_p2->push(1);
        this->subdivobject_03_subdivider_synco->push(0);
        this->subdivobject_03_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_03_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_03_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_03_subdivider_div));
        number pv;

        if (this->subdivobject_03_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_03_subdivider_prob->length));
            pv = this->subdivobject_03_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_03_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_03_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_03_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_03_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_03_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_03_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_03_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_03_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_03_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_03_subdivider_prob->length));
                pv = this->subdivobject_03_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_03_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_03_subdivider_reset() {
    this->subdivobject_03_subdivider_outstep = 0;
    this->subdivobject_03_subdivider_posstep = 0;
    this->subdivobject_03_subdivider_probstep = 0;
    this->subdivobject_03_subdivider_lastoutstep = 0;
    this->subdivobject_03_subdivider_div = 1;
    this->subdivobject_03_subdivider_nextdiv = 1;
    this->subdivobject_03_subdivider_resolveSync();
    this->subdivobject_03_subdivider_playing = this->subdivobject_03_subdivider_isPlaying(0);
    this->subdivobject_03_subdivider_patternstep = 0;
}

void subdivobject_03_subdivider_dspsetup() {
    this->subdivobject_03_subdivider_reset();
    this->subdivobject_03_subdivider_rebuild();
}

void subdivobject_03_subdivider_init() {
    this->subdivobject_03_subdivider_reset();
    this->subdivobject_03_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_03_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_03_subdivider_prob, prob)[0]))) {
        this->subdivobject_03_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_03_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_03_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_03_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_03_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_03_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_03_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_03_subdivider_div ? this->subdivobject_03_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_03_subdivider_patternstep = 0;
        this->subdivobject_03_subdivider_rebuild();
    }
}

void subdivobject_03_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_03_subdivider_nextdiv) {
        this->subdivobject_03_subdivider_nextdiv = div;
    }
}

number subdivobject_03_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_03_subdivider_p2[(Index)(this->subdivobject_03_subdivider_patternstep + step)]);
    this->subdivobject_03_subdivider_patternphase = this->subdivobject_03_subdivider_synco[(Index)(this->subdivobject_03_subdivider_patternstep + step)];

    if (step == this->subdivobject_03_subdivider_div - 1) {
        if (this->subdivobject_03_subdivider_patternstep + this->subdivobject_03_subdivider_div >= this->subdivobject_03_subdivider_p2length) {
            this->subdivobject_03_subdivider_patternstep = 0;
        } else {
            this->subdivobject_03_subdivider_patternstep += this->subdivobject_03_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_03_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_03_subdivider_p2prob[(Index)(this->subdivobject_03_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_03_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_03_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_03_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_03_subdivider_probstep);

        if (ps >= this->subdivobject_03_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_03_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_03_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_03_subdivider_getPatternProbability(step, this->subdivobject_03_subdivider_playing);
        }

        this->subdivobject_03_subdivider_num = this->subdivobject_03_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_03_subdivider_num = 1;

        if ((bool)(this->subdivobject_03_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_03_subdivider_prob->length));
            pv = this->subdivobject_03_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_03_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_03_subdivider_resolveSync() {
    if (this->subdivobject_03_subdivider_nextdiv != this->subdivobject_03_subdivider_div) {
        this->subdivobject_03_subdivider_div = this->subdivobject_03_subdivider_nextdiv;

        if (this->subdivobject_03_subdivider_pattern->length > 0) {
            this->subdivobject_03_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_03_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_03_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_03_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_03_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_03_subdivider_div);

    if (this->subdivobject_03_subdivider_posstep >= div) {
        this->subdivobject_03_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_03_subdivider_detectReset(
        val,
        this->subdivobject_03_subdivider_prev,
        this->subdivobject_03_subdivider_prev2
    ))) {
        this->subdivobject_03_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_03_subdivider_resolveSync();
            div = this->subdivobject_03_subdivider_div;
        }

        if ((bool)(this->subdivobject_03_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_03_subdivider_lockprob))) {
            if (this->subdivobject_03_subdivider_probstep >= this->subdivobject_03_subdivider_prob->length) {
                this->subdivobject_03_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_03_subdivider_playing = this->subdivobject_03_subdivider_isPlaying(this->subdivobject_03_subdivider_posstep);
    }

    this->subdivobject_03_subdivider_prev2 = this->subdivobject_03_subdivider_prev;
    this->subdivobject_03_subdivider_prev = val;
    val *= div;
    this->subdivobject_03_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_03_subdivider_patternphase;
    val /= this->subdivobject_03_subdivider_num;
    this->subdivobject_03_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_03_subdivider_nextoutstep != this->subdivobject_03_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_03_subdivider_resolveSync();
            div = this->subdivobject_03_subdivider_div;
        }

        this->subdivobject_03_subdivider_outstep = this->subdivobject_03_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_03_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_03_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_03_subdivider_probstep += 1;

            if (this->subdivobject_03_subdivider_probstep >= this->subdivobject_03_subdivider_prob->length) {
                this->subdivobject_03_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_03_subdivider_nextposstep != this->subdivobject_03_subdivider_posstep) {
        this->subdivobject_03_subdivider_posstep = this->subdivobject_03_subdivider_nextposstep;
        this->subdivobject_03_subdivider_playing = this->subdivobject_03_subdivider_isPlaying(this->subdivobject_03_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_03_subdivider_playing)) {
        out1 = val - this->subdivobject_03_subdivider_nextoutstep;
        out2 = this->subdivobject_03_subdivider_nextoutstep;
        this->subdivobject_03_subdivider_lastoutstep = this->subdivobject_03_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_03_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_03_dspsetup(bool force) {
    if ((bool)(this->subdivobject_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_03_setupDone = true;
    this->subdivobject_03_subdivider_dspsetup();
}

void delta_tilde_04_reset() {
    this->delta_tilde_04_prev = 0;
}

void delta_tilde_04_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_04_reset();
    this->delta_tilde_04_setupDone = true;
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void subdivobject_04_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_04_subdivider_pattern->length == 0) {
        this->subdivobject_04_subdivider_p2length = 0;
        this->subdivobject_04_subdivider_patternstep = 0;
        this->subdivobject_04_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_04_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_04_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_04_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_04_subdivider_div - i));

    if (this->subdivobject_04_subdivider_p2length != totalsteps) {
        this->subdivobject_04_subdivider_p2length = totalsteps;
    }

    this->subdivobject_04_subdivider_p2 = {};
    this->subdivobject_04_subdivider_synco = {};
    this->subdivobject_04_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_04_subdivider_p2->push(1);
        this->subdivobject_04_subdivider_synco->push(0);
        this->subdivobject_04_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_04_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_04_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_04_subdivider_div));
        number pv;

        if (this->subdivobject_04_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_04_subdivider_prob->length));
            pv = this->subdivobject_04_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_04_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_04_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_04_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_04_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_04_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_04_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_04_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_04_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_04_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_04_subdivider_prob->length));
                pv = this->subdivobject_04_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_04_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_04_subdivider_reset() {
    this->subdivobject_04_subdivider_outstep = 0;
    this->subdivobject_04_subdivider_posstep = 0;
    this->subdivobject_04_subdivider_probstep = 0;
    this->subdivobject_04_subdivider_lastoutstep = 0;
    this->subdivobject_04_subdivider_div = 1;
    this->subdivobject_04_subdivider_nextdiv = 1;
    this->subdivobject_04_subdivider_resolveSync();
    this->subdivobject_04_subdivider_playing = this->subdivobject_04_subdivider_isPlaying(0);
    this->subdivobject_04_subdivider_patternstep = 0;
}

void subdivobject_04_subdivider_dspsetup() {
    this->subdivobject_04_subdivider_reset();
    this->subdivobject_04_subdivider_rebuild();
}

void subdivobject_04_subdivider_init() {
    this->subdivobject_04_subdivider_reset();
    this->subdivobject_04_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_04_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_04_subdivider_prob, prob)[0]))) {
        this->subdivobject_04_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_04_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_04_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_04_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_04_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_04_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_04_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_04_subdivider_div ? this->subdivobject_04_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_04_subdivider_patternstep = 0;
        this->subdivobject_04_subdivider_rebuild();
    }
}

void subdivobject_04_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_04_subdivider_nextdiv) {
        this->subdivobject_04_subdivider_nextdiv = div;
    }
}

number subdivobject_04_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_04_subdivider_p2[(Index)(this->subdivobject_04_subdivider_patternstep + step)]);
    this->subdivobject_04_subdivider_patternphase = this->subdivobject_04_subdivider_synco[(Index)(this->subdivobject_04_subdivider_patternstep + step)];

    if (step == this->subdivobject_04_subdivider_div - 1) {
        if (this->subdivobject_04_subdivider_patternstep + this->subdivobject_04_subdivider_div >= this->subdivobject_04_subdivider_p2length) {
            this->subdivobject_04_subdivider_patternstep = 0;
        } else {
            this->subdivobject_04_subdivider_patternstep += this->subdivobject_04_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_04_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_04_subdivider_p2prob[(Index)(this->subdivobject_04_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_04_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_04_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_04_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_04_subdivider_probstep);

        if (ps >= this->subdivobject_04_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_04_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_04_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_04_subdivider_getPatternProbability(step, this->subdivobject_04_subdivider_playing);
        }

        this->subdivobject_04_subdivider_num = this->subdivobject_04_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_04_subdivider_num = 1;

        if ((bool)(this->subdivobject_04_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_04_subdivider_prob->length));
            pv = this->subdivobject_04_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_04_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_04_subdivider_resolveSync() {
    if (this->subdivobject_04_subdivider_nextdiv != this->subdivobject_04_subdivider_div) {
        this->subdivobject_04_subdivider_div = this->subdivobject_04_subdivider_nextdiv;

        if (this->subdivobject_04_subdivider_pattern->length > 0) {
            this->subdivobject_04_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_04_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_04_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_04_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_04_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_04_subdivider_div);

    if (this->subdivobject_04_subdivider_posstep >= div) {
        this->subdivobject_04_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_04_subdivider_detectReset(
        val,
        this->subdivobject_04_subdivider_prev,
        this->subdivobject_04_subdivider_prev2
    ))) {
        this->subdivobject_04_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_04_subdivider_resolveSync();
            div = this->subdivobject_04_subdivider_div;
        }

        if ((bool)(this->subdivobject_04_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_04_subdivider_lockprob))) {
            if (this->subdivobject_04_subdivider_probstep >= this->subdivobject_04_subdivider_prob->length) {
                this->subdivobject_04_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_04_subdivider_playing = this->subdivobject_04_subdivider_isPlaying(this->subdivobject_04_subdivider_posstep);
    }

    this->subdivobject_04_subdivider_prev2 = this->subdivobject_04_subdivider_prev;
    this->subdivobject_04_subdivider_prev = val;
    val *= div;
    this->subdivobject_04_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_04_subdivider_patternphase;
    val /= this->subdivobject_04_subdivider_num;
    this->subdivobject_04_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_04_subdivider_nextoutstep != this->subdivobject_04_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_04_subdivider_resolveSync();
            div = this->subdivobject_04_subdivider_div;
        }

        this->subdivobject_04_subdivider_outstep = this->subdivobject_04_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_04_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_04_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_04_subdivider_probstep += 1;

            if (this->subdivobject_04_subdivider_probstep >= this->subdivobject_04_subdivider_prob->length) {
                this->subdivobject_04_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_04_subdivider_nextposstep != this->subdivobject_04_subdivider_posstep) {
        this->subdivobject_04_subdivider_posstep = this->subdivobject_04_subdivider_nextposstep;
        this->subdivobject_04_subdivider_playing = this->subdivobject_04_subdivider_isPlaying(this->subdivobject_04_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_04_subdivider_playing)) {
        out1 = val - this->subdivobject_04_subdivider_nextoutstep;
        out2 = this->subdivobject_04_subdivider_nextoutstep;
        this->subdivobject_04_subdivider_lastoutstep = this->subdivobject_04_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_04_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_04_dspsetup(bool force) {
    if ((bool)(this->subdivobject_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_04_setupDone = true;
    this->subdivobject_04_subdivider_dspsetup();
}

void delta_tilde_05_reset() {
    this->delta_tilde_05_prev = 0;
}

void delta_tilde_05_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_05_reset();
    this->delta_tilde_05_setupDone = true;
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void subdivobject_05_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_05_subdivider_pattern->length == 0) {
        this->subdivobject_05_subdivider_p2length = 0;
        this->subdivobject_05_subdivider_patternstep = 0;
        this->subdivobject_05_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_05_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_05_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_05_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_05_subdivider_div - i));

    if (this->subdivobject_05_subdivider_p2length != totalsteps) {
        this->subdivobject_05_subdivider_p2length = totalsteps;
    }

    this->subdivobject_05_subdivider_p2 = {};
    this->subdivobject_05_subdivider_synco = {};
    this->subdivobject_05_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_05_subdivider_p2->push(1);
        this->subdivobject_05_subdivider_synco->push(0);
        this->subdivobject_05_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_05_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_05_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_05_subdivider_div));
        number pv;

        if (this->subdivobject_05_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_05_subdivider_prob->length));
            pv = this->subdivobject_05_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_05_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_05_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_05_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_05_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_05_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_05_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_05_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_05_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_05_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_05_subdivider_prob->length));
                pv = this->subdivobject_05_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_05_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_05_subdivider_reset() {
    this->subdivobject_05_subdivider_outstep = 0;
    this->subdivobject_05_subdivider_posstep = 0;
    this->subdivobject_05_subdivider_probstep = 0;
    this->subdivobject_05_subdivider_lastoutstep = 0;
    this->subdivobject_05_subdivider_div = 1;
    this->subdivobject_05_subdivider_nextdiv = 1;
    this->subdivobject_05_subdivider_resolveSync();
    this->subdivobject_05_subdivider_playing = this->subdivobject_05_subdivider_isPlaying(0);
    this->subdivobject_05_subdivider_patternstep = 0;
}

void subdivobject_05_subdivider_dspsetup() {
    this->subdivobject_05_subdivider_reset();
    this->subdivobject_05_subdivider_rebuild();
}

void subdivobject_05_subdivider_init() {
    this->subdivobject_05_subdivider_reset();
    this->subdivobject_05_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_05_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_05_subdivider_prob, prob)[0]))) {
        this->subdivobject_05_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_05_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_05_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_05_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_05_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_05_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_05_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_05_subdivider_div ? this->subdivobject_05_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_05_subdivider_patternstep = 0;
        this->subdivobject_05_subdivider_rebuild();
    }
}

void subdivobject_05_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_05_subdivider_nextdiv) {
        this->subdivobject_05_subdivider_nextdiv = div;
    }
}

number subdivobject_05_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_05_subdivider_p2[(Index)(this->subdivobject_05_subdivider_patternstep + step)]);
    this->subdivobject_05_subdivider_patternphase = this->subdivobject_05_subdivider_synco[(Index)(this->subdivobject_05_subdivider_patternstep + step)];

    if (step == this->subdivobject_05_subdivider_div - 1) {
        if (this->subdivobject_05_subdivider_patternstep + this->subdivobject_05_subdivider_div >= this->subdivobject_05_subdivider_p2length) {
            this->subdivobject_05_subdivider_patternstep = 0;
        } else {
            this->subdivobject_05_subdivider_patternstep += this->subdivobject_05_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_05_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_05_subdivider_p2prob[(Index)(this->subdivobject_05_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_05_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_05_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_05_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_05_subdivider_probstep);

        if (ps >= this->subdivobject_05_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_05_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_05_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_05_subdivider_getPatternProbability(step, this->subdivobject_05_subdivider_playing);
        }

        this->subdivobject_05_subdivider_num = this->subdivobject_05_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_05_subdivider_num = 1;

        if ((bool)(this->subdivobject_05_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_05_subdivider_prob->length));
            pv = this->subdivobject_05_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_05_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_05_subdivider_resolveSync() {
    if (this->subdivobject_05_subdivider_nextdiv != this->subdivobject_05_subdivider_div) {
        this->subdivobject_05_subdivider_div = this->subdivobject_05_subdivider_nextdiv;

        if (this->subdivobject_05_subdivider_pattern->length > 0) {
            this->subdivobject_05_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_05_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_05_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_05_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_05_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_05_subdivider_div);

    if (this->subdivobject_05_subdivider_posstep >= div) {
        this->subdivobject_05_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_05_subdivider_detectReset(
        val,
        this->subdivobject_05_subdivider_prev,
        this->subdivobject_05_subdivider_prev2
    ))) {
        this->subdivobject_05_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_05_subdivider_resolveSync();
            div = this->subdivobject_05_subdivider_div;
        }

        if ((bool)(this->subdivobject_05_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_05_subdivider_lockprob))) {
            if (this->subdivobject_05_subdivider_probstep >= this->subdivobject_05_subdivider_prob->length) {
                this->subdivobject_05_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_05_subdivider_playing = this->subdivobject_05_subdivider_isPlaying(this->subdivobject_05_subdivider_posstep);
    }

    this->subdivobject_05_subdivider_prev2 = this->subdivobject_05_subdivider_prev;
    this->subdivobject_05_subdivider_prev = val;
    val *= div;
    this->subdivobject_05_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_05_subdivider_patternphase;
    val /= this->subdivobject_05_subdivider_num;
    this->subdivobject_05_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_05_subdivider_nextoutstep != this->subdivobject_05_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_05_subdivider_resolveSync();
            div = this->subdivobject_05_subdivider_div;
        }

        this->subdivobject_05_subdivider_outstep = this->subdivobject_05_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_05_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_05_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_05_subdivider_probstep += 1;

            if (this->subdivobject_05_subdivider_probstep >= this->subdivobject_05_subdivider_prob->length) {
                this->subdivobject_05_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_05_subdivider_nextposstep != this->subdivobject_05_subdivider_posstep) {
        this->subdivobject_05_subdivider_posstep = this->subdivobject_05_subdivider_nextposstep;
        this->subdivobject_05_subdivider_playing = this->subdivobject_05_subdivider_isPlaying(this->subdivobject_05_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_05_subdivider_playing)) {
        out1 = val - this->subdivobject_05_subdivider_nextoutstep;
        out2 = this->subdivobject_05_subdivider_nextoutstep;
        this->subdivobject_05_subdivider_lastoutstep = this->subdivobject_05_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_05_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_05_dspsetup(bool force) {
    if ((bool)(this->subdivobject_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_05_setupDone = true;
    this->subdivobject_05_subdivider_dspsetup();
}

void delta_tilde_06_reset() {
    this->delta_tilde_06_prev = 0;
}

void delta_tilde_06_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_06_reset();
    this->delta_tilde_06_setupDone = true;
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void subdivobject_06_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_06_subdivider_pattern->length == 0) {
        this->subdivobject_06_subdivider_p2length = 0;
        this->subdivobject_06_subdivider_patternstep = 0;
        this->subdivobject_06_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_06_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_06_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_06_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_06_subdivider_div - i));

    if (this->subdivobject_06_subdivider_p2length != totalsteps) {
        this->subdivobject_06_subdivider_p2length = totalsteps;
    }

    this->subdivobject_06_subdivider_p2 = {};
    this->subdivobject_06_subdivider_synco = {};
    this->subdivobject_06_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_06_subdivider_p2->push(1);
        this->subdivobject_06_subdivider_synco->push(0);
        this->subdivobject_06_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_06_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_06_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_06_subdivider_div));
        number pv;

        if (this->subdivobject_06_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_06_subdivider_prob->length));
            pv = this->subdivobject_06_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_06_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_06_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_06_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_06_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_06_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_06_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_06_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_06_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_06_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_06_subdivider_prob->length));
                pv = this->subdivobject_06_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_06_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_06_subdivider_reset() {
    this->subdivobject_06_subdivider_outstep = 0;
    this->subdivobject_06_subdivider_posstep = 0;
    this->subdivobject_06_subdivider_probstep = 0;
    this->subdivobject_06_subdivider_lastoutstep = 0;
    this->subdivobject_06_subdivider_div = 1;
    this->subdivobject_06_subdivider_nextdiv = 1;
    this->subdivobject_06_subdivider_resolveSync();
    this->subdivobject_06_subdivider_playing = this->subdivobject_06_subdivider_isPlaying(0);
    this->subdivobject_06_subdivider_patternstep = 0;
}

void subdivobject_06_subdivider_dspsetup() {
    this->subdivobject_06_subdivider_reset();
    this->subdivobject_06_subdivider_rebuild();
}

void subdivobject_06_subdivider_init() {
    this->subdivobject_06_subdivider_reset();
    this->subdivobject_06_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_06_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_06_subdivider_prob, prob)[0]))) {
        this->subdivobject_06_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_06_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_06_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_06_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_06_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_06_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_06_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_06_subdivider_div ? this->subdivobject_06_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_06_subdivider_patternstep = 0;
        this->subdivobject_06_subdivider_rebuild();
    }
}

void subdivobject_06_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_06_subdivider_nextdiv) {
        this->subdivobject_06_subdivider_nextdiv = div;
    }
}

number subdivobject_06_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_06_subdivider_p2[(Index)(this->subdivobject_06_subdivider_patternstep + step)]);
    this->subdivobject_06_subdivider_patternphase = this->subdivobject_06_subdivider_synco[(Index)(this->subdivobject_06_subdivider_patternstep + step)];

    if (step == this->subdivobject_06_subdivider_div - 1) {
        if (this->subdivobject_06_subdivider_patternstep + this->subdivobject_06_subdivider_div >= this->subdivobject_06_subdivider_p2length) {
            this->subdivobject_06_subdivider_patternstep = 0;
        } else {
            this->subdivobject_06_subdivider_patternstep += this->subdivobject_06_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_06_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_06_subdivider_p2prob[(Index)(this->subdivobject_06_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_06_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_06_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_06_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_06_subdivider_probstep);

        if (ps >= this->subdivobject_06_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_06_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_06_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_06_subdivider_getPatternProbability(step, this->subdivobject_06_subdivider_playing);
        }

        this->subdivobject_06_subdivider_num = this->subdivobject_06_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_06_subdivider_num = 1;

        if ((bool)(this->subdivobject_06_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_06_subdivider_prob->length));
            pv = this->subdivobject_06_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_06_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_06_subdivider_resolveSync() {
    if (this->subdivobject_06_subdivider_nextdiv != this->subdivobject_06_subdivider_div) {
        this->subdivobject_06_subdivider_div = this->subdivobject_06_subdivider_nextdiv;

        if (this->subdivobject_06_subdivider_pattern->length > 0) {
            this->subdivobject_06_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_06_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_06_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_06_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_06_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_06_subdivider_div);

    if (this->subdivobject_06_subdivider_posstep >= div) {
        this->subdivobject_06_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_06_subdivider_detectReset(
        val,
        this->subdivobject_06_subdivider_prev,
        this->subdivobject_06_subdivider_prev2
    ))) {
        this->subdivobject_06_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_06_subdivider_resolveSync();
            div = this->subdivobject_06_subdivider_div;
        }

        if ((bool)(this->subdivobject_06_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_06_subdivider_lockprob))) {
            if (this->subdivobject_06_subdivider_probstep >= this->subdivobject_06_subdivider_prob->length) {
                this->subdivobject_06_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_06_subdivider_playing = this->subdivobject_06_subdivider_isPlaying(this->subdivobject_06_subdivider_posstep);
    }

    this->subdivobject_06_subdivider_prev2 = this->subdivobject_06_subdivider_prev;
    this->subdivobject_06_subdivider_prev = val;
    val *= div;
    this->subdivobject_06_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_06_subdivider_patternphase;
    val /= this->subdivobject_06_subdivider_num;
    this->subdivobject_06_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_06_subdivider_nextoutstep != this->subdivobject_06_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_06_subdivider_resolveSync();
            div = this->subdivobject_06_subdivider_div;
        }

        this->subdivobject_06_subdivider_outstep = this->subdivobject_06_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_06_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_06_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_06_subdivider_probstep += 1;

            if (this->subdivobject_06_subdivider_probstep >= this->subdivobject_06_subdivider_prob->length) {
                this->subdivobject_06_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_06_subdivider_nextposstep != this->subdivobject_06_subdivider_posstep) {
        this->subdivobject_06_subdivider_posstep = this->subdivobject_06_subdivider_nextposstep;
        this->subdivobject_06_subdivider_playing = this->subdivobject_06_subdivider_isPlaying(this->subdivobject_06_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_06_subdivider_playing)) {
        out1 = val - this->subdivobject_06_subdivider_nextoutstep;
        out2 = this->subdivobject_06_subdivider_nextoutstep;
        this->subdivobject_06_subdivider_lastoutstep = this->subdivobject_06_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_06_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_06_dspsetup(bool force) {
    if ((bool)(this->subdivobject_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_06_setupDone = true;
    this->subdivobject_06_subdivider_dspsetup();
}

void delta_tilde_07_reset() {
    this->delta_tilde_07_prev = 0;
}

void delta_tilde_07_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_07_reset();
    this->delta_tilde_07_setupDone = true;
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void subdivobject_07_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_07_subdivider_pattern->length == 0) {
        this->subdivobject_07_subdivider_p2length = 0;
        this->subdivobject_07_subdivider_patternstep = 0;
        this->subdivobject_07_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_07_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_07_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_07_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_07_subdivider_div - i));

    if (this->subdivobject_07_subdivider_p2length != totalsteps) {
        this->subdivobject_07_subdivider_p2length = totalsteps;
    }

    this->subdivobject_07_subdivider_p2 = {};
    this->subdivobject_07_subdivider_synco = {};
    this->subdivobject_07_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_07_subdivider_p2->push(1);
        this->subdivobject_07_subdivider_synco->push(0);
        this->subdivobject_07_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_07_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_07_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_07_subdivider_div));
        number pv;

        if (this->subdivobject_07_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_07_subdivider_prob->length));
            pv = this->subdivobject_07_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_07_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_07_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_07_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_07_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_07_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_07_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_07_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_07_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_07_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_07_subdivider_prob->length));
                pv = this->subdivobject_07_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_07_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_07_subdivider_reset() {
    this->subdivobject_07_subdivider_outstep = 0;
    this->subdivobject_07_subdivider_posstep = 0;
    this->subdivobject_07_subdivider_probstep = 0;
    this->subdivobject_07_subdivider_lastoutstep = 0;
    this->subdivobject_07_subdivider_div = 1;
    this->subdivobject_07_subdivider_nextdiv = 1;
    this->subdivobject_07_subdivider_resolveSync();
    this->subdivobject_07_subdivider_playing = this->subdivobject_07_subdivider_isPlaying(0);
    this->subdivobject_07_subdivider_patternstep = 0;
}

void subdivobject_07_subdivider_dspsetup() {
    this->subdivobject_07_subdivider_reset();
    this->subdivobject_07_subdivider_rebuild();
}

void subdivobject_07_subdivider_init() {
    this->subdivobject_07_subdivider_reset();
    this->subdivobject_07_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_07_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_07_subdivider_prob, prob)[0]))) {
        this->subdivobject_07_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_07_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_07_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_07_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_07_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_07_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_07_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_07_subdivider_div ? this->subdivobject_07_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_07_subdivider_patternstep = 0;
        this->subdivobject_07_subdivider_rebuild();
    }
}

void subdivobject_07_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_07_subdivider_nextdiv) {
        this->subdivobject_07_subdivider_nextdiv = div;
    }
}

number subdivobject_07_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_07_subdivider_p2[(Index)(this->subdivobject_07_subdivider_patternstep + step)]);
    this->subdivobject_07_subdivider_patternphase = this->subdivobject_07_subdivider_synco[(Index)(this->subdivobject_07_subdivider_patternstep + step)];

    if (step == this->subdivobject_07_subdivider_div - 1) {
        if (this->subdivobject_07_subdivider_patternstep + this->subdivobject_07_subdivider_div >= this->subdivobject_07_subdivider_p2length) {
            this->subdivobject_07_subdivider_patternstep = 0;
        } else {
            this->subdivobject_07_subdivider_patternstep += this->subdivobject_07_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_07_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_07_subdivider_p2prob[(Index)(this->subdivobject_07_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_07_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_07_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_07_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_07_subdivider_probstep);

        if (ps >= this->subdivobject_07_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_07_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_07_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_07_subdivider_getPatternProbability(step, this->subdivobject_07_subdivider_playing);
        }

        this->subdivobject_07_subdivider_num = this->subdivobject_07_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_07_subdivider_num = 1;

        if ((bool)(this->subdivobject_07_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_07_subdivider_prob->length));
            pv = this->subdivobject_07_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_07_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_07_subdivider_resolveSync() {
    if (this->subdivobject_07_subdivider_nextdiv != this->subdivobject_07_subdivider_div) {
        this->subdivobject_07_subdivider_div = this->subdivobject_07_subdivider_nextdiv;

        if (this->subdivobject_07_subdivider_pattern->length > 0) {
            this->subdivobject_07_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_07_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_07_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_07_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_07_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_07_subdivider_div);

    if (this->subdivobject_07_subdivider_posstep >= div) {
        this->subdivobject_07_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_07_subdivider_detectReset(
        val,
        this->subdivobject_07_subdivider_prev,
        this->subdivobject_07_subdivider_prev2
    ))) {
        this->subdivobject_07_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_07_subdivider_resolveSync();
            div = this->subdivobject_07_subdivider_div;
        }

        if ((bool)(this->subdivobject_07_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_07_subdivider_lockprob))) {
            if (this->subdivobject_07_subdivider_probstep >= this->subdivobject_07_subdivider_prob->length) {
                this->subdivobject_07_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_07_subdivider_playing = this->subdivobject_07_subdivider_isPlaying(this->subdivobject_07_subdivider_posstep);
    }

    this->subdivobject_07_subdivider_prev2 = this->subdivobject_07_subdivider_prev;
    this->subdivobject_07_subdivider_prev = val;
    val *= div;
    this->subdivobject_07_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_07_subdivider_patternphase;
    val /= this->subdivobject_07_subdivider_num;
    this->subdivobject_07_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_07_subdivider_nextoutstep != this->subdivobject_07_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_07_subdivider_resolveSync();
            div = this->subdivobject_07_subdivider_div;
        }

        this->subdivobject_07_subdivider_outstep = this->subdivobject_07_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_07_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_07_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_07_subdivider_probstep += 1;

            if (this->subdivobject_07_subdivider_probstep >= this->subdivobject_07_subdivider_prob->length) {
                this->subdivobject_07_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_07_subdivider_nextposstep != this->subdivobject_07_subdivider_posstep) {
        this->subdivobject_07_subdivider_posstep = this->subdivobject_07_subdivider_nextposstep;
        this->subdivobject_07_subdivider_playing = this->subdivobject_07_subdivider_isPlaying(this->subdivobject_07_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_07_subdivider_playing)) {
        out1 = val - this->subdivobject_07_subdivider_nextoutstep;
        out2 = this->subdivobject_07_subdivider_nextoutstep;
        this->subdivobject_07_subdivider_lastoutstep = this->subdivobject_07_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_07_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_07_dspsetup(bool force) {
    if ((bool)(this->subdivobject_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_07_setupDone = true;
    this->subdivobject_07_subdivider_dspsetup();
}

void delta_tilde_08_reset() {
    this->delta_tilde_08_prev = 0;
}

void delta_tilde_08_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_08_reset();
    this->delta_tilde_08_setupDone = true;
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void subdivobject_08_subdivider_rebuild() {
    number i; number j; number c; number totaltime; number totalsteps;

    if (this->subdivobject_08_subdivider_pattern->length == 0) {
        this->subdivobject_08_subdivider_p2length = 0;
        this->subdivobject_08_subdivider_patternstep = 0;
        this->subdivobject_08_subdivider_patternphase = 0;
        return;
    }

    totaltime = 0;

    for (i = 0; i < this->subdivobject_08_subdivider_pattern->length; i++) {
        totaltime += this->subdivobject_08_subdivider_pattern[(Index)i];
    }

    i = this->safemod(totaltime, this->subdivobject_08_subdivider_div);
    totalsteps = (i == 0 ? totaltime : totaltime + (this->subdivobject_08_subdivider_div - i));

    if (this->subdivobject_08_subdivider_p2length != totalsteps) {
        this->subdivobject_08_subdivider_p2length = totalsteps;
    }

    this->subdivobject_08_subdivider_p2 = {};
    this->subdivobject_08_subdivider_synco = {};
    this->subdivobject_08_subdivider_p2prob = {};

    for (number i = 0; i < totalsteps; i++) {
        this->subdivobject_08_subdivider_p2->push(1);
        this->subdivobject_08_subdivider_synco->push(0);
        this->subdivobject_08_subdivider_p2prob->push(1.0);
    }

    totaltime = 0;
    c = 0;

    for (i = 0; i < this->subdivobject_08_subdivider_pattern->length; i++) {
        number nextvalue = (number)(this->subdivobject_08_subdivider_pattern[(Index)i]);
        number nextstart = (number)(this->safemod(totaltime, this->subdivobject_08_subdivider_div));
        number pv;

        if (this->subdivobject_08_subdivider_prob->length > 0) {
            number ps = (number)(this->safemod(i, this->subdivobject_08_subdivider_prob->length));
            pv = this->subdivobject_08_subdivider_prob[(Index)ps];
        } else {
            pv = 1.0;
        }

        for (j = 0; j < nextvalue; j++) {
            this->subdivobject_08_subdivider_p2[(Index)c] = nextvalue;

            if (nextvalue > 1)
                this->subdivobject_08_subdivider_synco[(Index)c] = nextstart;
            else
                this->subdivobject_08_subdivider_synco[(Index)c] = 0;

            if (j == 0)
                this->subdivobject_08_subdivider_p2prob[(Index)c] = pv;
            else
                this->subdivobject_08_subdivider_p2prob[(Index)c] = -1;

            c++;
        }

        totaltime += nextvalue;
    }

    for (j = 0; c < totalsteps; c++, j++) {
        number pv = 1.0;
        this->subdivobject_08_subdivider_p2[(Index)c] = totalsteps - totaltime;
        this->subdivobject_08_subdivider_synco[(Index)c] = this->safemod(totaltime, this->subdivobject_08_subdivider_div);

        if (j == 0) {
            if (this->subdivobject_08_subdivider_prob->length > 0) {
                number ps = (number)(this->safemod(i, this->subdivobject_08_subdivider_prob->length));
                pv = this->subdivobject_08_subdivider_prob[(Index)ps];
            } else {
                pv = 1.0;
            }
        } else {
            pv = -1.0;
        }

        this->subdivobject_08_subdivider_p2prob[(Index)c] = pv;
    }
}

void subdivobject_08_subdivider_reset() {
    this->subdivobject_08_subdivider_outstep = 0;
    this->subdivobject_08_subdivider_posstep = 0;
    this->subdivobject_08_subdivider_probstep = 0;
    this->subdivobject_08_subdivider_lastoutstep = 0;
    this->subdivobject_08_subdivider_div = 1;
    this->subdivobject_08_subdivider_nextdiv = 1;
    this->subdivobject_08_subdivider_resolveSync();
    this->subdivobject_08_subdivider_playing = this->subdivobject_08_subdivider_isPlaying(0);
    this->subdivobject_08_subdivider_patternstep = 0;
}

void subdivobject_08_subdivider_dspsetup() {
    this->subdivobject_08_subdivider_reset();
    this->subdivobject_08_subdivider_rebuild();
}

void subdivobject_08_subdivider_init() {
    this->subdivobject_08_subdivider_reset();
    this->subdivobject_08_subdivider_rebuild();
}

template<typename LISTTYPE = list> void subdivobject_08_subdivider_setProb(const LISTTYPE& prob) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_08_subdivider_prob, prob)[0]))) {
        this->subdivobject_08_subdivider_prob = {};

        if (prob->length > 0) {
            for (number i = 0; i < prob->length; i++) {
                this->subdivobject_08_subdivider_prob->push(
                    (prob[(Index)i] > 1.0 ? 1.0 : (prob[(Index)i] < 0.0 ? 0.0 : prob[(Index)i]))
                );
            }
        }

        this->subdivobject_08_subdivider_rebuild();
    }
}

template<typename LISTTYPE = list> void subdivobject_08_subdivider_setPattern(const LISTTYPE& pattern) {
    if ((bool)(!(bool)(this->listcompare(this->subdivobject_08_subdivider_pattern, pattern)[0]))) {
        this->subdivobject_08_subdivider_pattern = {};

        if (pattern->length > 0) {
            for (number i = 0; i < pattern->length; i++) {
                this->subdivobject_08_subdivider_pattern->push(
                    (pattern[(Index)i] > this->subdivobject_08_subdivider_div ? this->subdivobject_08_subdivider_div : (pattern[(Index)i] < 1 ? 1 : pattern[(Index)i]))
                );
            }
        }

        this->subdivobject_08_subdivider_patternstep = 0;
        this->subdivobject_08_subdivider_rebuild();
    }
}

void subdivobject_08_subdivider_setDiv(Int div) {
    if (div != this->subdivobject_08_subdivider_nextdiv) {
        this->subdivobject_08_subdivider_nextdiv = div;
    }
}

number subdivobject_08_subdivider_getPatternNumerator(number step) {
    number value = (number)(this->subdivobject_08_subdivider_p2[(Index)(this->subdivobject_08_subdivider_patternstep + step)]);
    this->subdivobject_08_subdivider_patternphase = this->subdivobject_08_subdivider_synco[(Index)(this->subdivobject_08_subdivider_patternstep + step)];

    if (step == this->subdivobject_08_subdivider_div - 1) {
        if (this->subdivobject_08_subdivider_patternstep + this->subdivobject_08_subdivider_div >= this->subdivobject_08_subdivider_p2length) {
            this->subdivobject_08_subdivider_patternstep = 0;
        } else {
            this->subdivobject_08_subdivider_patternstep += this->subdivobject_08_subdivider_div;
        }
    }

    return value;
}

bool subdivobject_08_subdivider_getPatternProbability(number step, bool playing) {
    number pv = (number)(this->subdivobject_08_subdivider_p2prob[(Index)(this->subdivobject_08_subdivider_patternstep + step)]);

    if (pv == -1) {
        return playing;
    }

    if (pv == 0) {
        return false;
    }

    if (pv == 1) {
        return true;
    }

    return this->random(0, 1) < pv;
}

bool subdivobject_08_subdivider_isPlaying(number step) {
    bool result = false;
    bool decided = false;
    number pv;

    if (this->subdivobject_08_subdivider_prob->length > 0 && (bool)(!(bool)(this->subdivobject_08_subdivider_lockprob))) {
        number ps = (number)(this->subdivobject_08_subdivider_probstep);

        if (ps >= this->subdivobject_08_subdivider_prob->length) {
            ps = 0;
        }

        pv = this->subdivobject_08_subdivider_prob[(Index)ps];
        result = this->random(0, 1) < pv;
        decided = true;
    }

    if (this->subdivobject_08_subdivider_pattern->length > 0) {
        if ((bool)(!(bool)(decided))) {
            result = this->subdivobject_08_subdivider_getPatternProbability(step, this->subdivobject_08_subdivider_playing);
        }

        this->subdivobject_08_subdivider_num = this->subdivobject_08_subdivider_getPatternNumerator(step);
    } else {
        this->subdivobject_08_subdivider_num = 1;

        if ((bool)(this->subdivobject_08_subdivider_prob->length) && (bool)(!(bool)(decided))) {
            number index = (number)(this->safemod(step, this->subdivobject_08_subdivider_prob->length));
            pv = this->subdivobject_08_subdivider_prob[(Index)index];

            if (pv == 0) {
                return false;
            }

            if (pv == 1) {
                return true;
            }

            return this->random(0, 1) < pv;
        } else if ((bool)(!(bool)(decided))) {
            result = true;
        }
    }

    return result;
}

bool subdivobject_08_subdivider_detectReset(number v, number p, number p2) {
    if (p2 < p && v < p && p - v > 0.25) {
        return true;
    }

    if (p2 > p && v > p && v - p > 0.25) {
        return true;
    }

    return false;
}

void subdivobject_08_subdivider_resolveSync() {
    if (this->subdivobject_08_subdivider_nextdiv != this->subdivobject_08_subdivider_div) {
        this->subdivobject_08_subdivider_div = this->subdivobject_08_subdivider_nextdiv;

        if (this->subdivobject_08_subdivider_pattern->length > 0) {
            this->subdivobject_08_subdivider_rebuild();
        }
    }
}

array<number, 2> subdivobject_08_subdivider_next(number x, number divarg, Int syncupdate, bool lockprob, bool silentmode) {
    this->subdivobject_08_subdivider_lockprob = lockprob;
    divarg = (divarg > 16384 ? 16384 : (divarg < 1 ? 1 : divarg));
    this->subdivobject_08_subdivider_setDiv(divarg);

    if (syncupdate == 0) {
        this->subdivobject_08_subdivider_resolveSync();
    }

    number div = (number)(this->subdivobject_08_subdivider_div);

    if (this->subdivobject_08_subdivider_posstep >= div) {
        this->subdivobject_08_subdivider_posstep = 0;
    }

    bool steppedalready = false;
    number val = (number)(x);

    if ((bool)(this->subdivobject_08_subdivider_detectReset(
        val,
        this->subdivobject_08_subdivider_prev,
        this->subdivobject_08_subdivider_prev2
    ))) {
        this->subdivobject_08_subdivider_posstep = 0;

        if (syncupdate > 0) {
            this->subdivobject_08_subdivider_resolveSync();
            div = this->subdivobject_08_subdivider_div;
        }

        if ((bool)(this->subdivobject_08_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_08_subdivider_lockprob))) {
            if (this->subdivobject_08_subdivider_probstep >= this->subdivobject_08_subdivider_prob->length) {
                this->subdivobject_08_subdivider_probstep = 0;
            }

            steppedalready = true;
        }

        this->subdivobject_08_subdivider_playing = this->subdivobject_08_subdivider_isPlaying(this->subdivobject_08_subdivider_posstep);
    }

    this->subdivobject_08_subdivider_prev2 = this->subdivobject_08_subdivider_prev;
    this->subdivobject_08_subdivider_prev = val;
    val *= div;
    this->subdivobject_08_subdivider_nextposstep = trunc(val);
    val -= this->subdivobject_08_subdivider_patternphase;
    val /= this->subdivobject_08_subdivider_num;
    this->subdivobject_08_subdivider_nextoutstep = trunc(val);

    if (this->subdivobject_08_subdivider_nextoutstep != this->subdivobject_08_subdivider_outstep) {
        if (syncupdate == 1) {
            this->subdivobject_08_subdivider_resolveSync();
            div = this->subdivobject_08_subdivider_div;
        }

        this->subdivobject_08_subdivider_outstep = this->subdivobject_08_subdivider_nextoutstep;

        if ((bool)(this->subdivobject_08_subdivider_prob->length) && (bool)(!(bool)(this->subdivobject_08_subdivider_lockprob)) && (bool)(!(bool)(steppedalready))) {
            this->subdivobject_08_subdivider_probstep += 1;

            if (this->subdivobject_08_subdivider_probstep >= this->subdivobject_08_subdivider_prob->length) {
                this->subdivobject_08_subdivider_probstep = 0;
            }
        }
    }

    if (this->subdivobject_08_subdivider_nextposstep != this->subdivobject_08_subdivider_posstep) {
        this->subdivobject_08_subdivider_posstep = this->subdivobject_08_subdivider_nextposstep;
        this->subdivobject_08_subdivider_playing = this->subdivobject_08_subdivider_isPlaying(this->subdivobject_08_subdivider_posstep);
    }

    number out1; number out2;

    if ((bool)(this->subdivobject_08_subdivider_playing)) {
        out1 = val - this->subdivobject_08_subdivider_nextoutstep;
        out2 = this->subdivobject_08_subdivider_nextoutstep;
        this->subdivobject_08_subdivider_lastoutstep = this->subdivobject_08_subdivider_nextoutstep;
    } else {
        out1 = 0.0;
        out2 = (silentmode == 0 ? this->subdivobject_08_subdivider_lastoutstep : -1);
    }

    return {out1, out2};
}

void subdivobject_08_dspsetup(bool force) {
    if ((bool)(this->subdivobject_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->subdivobject_08_setupDone = true;
    this->subdivobject_08_subdivider_dspsetup();
}

void delta_tilde_09_reset() {
    this->delta_tilde_09_prev = 0;
}

void delta_tilde_09_dspsetup(bool force) {
    if ((bool)(this->delta_tilde_09_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delta_tilde_09_reset();
    this->delta_tilde_09_setupDone = true;
}

void timevalue_01_sendValue() {
    {
        auto currentSig = this->timesignature();
        number ticksPerBeat = (number)1 / currentSig[1] * 4 * 480;
        number ticksPerBar = currentSig[0] * ticksPerBeat;
        list bbu = listbase<number, 3>{1, 0, 0};
        number tickValue = bbu[0] * ticksPerBar + bbu[1] * ticksPerBeat + bbu[2];

        {
            {
                {
                    {
                        this->timevalue_01_out_set(this->tickstohz(tickValue));
                    }
                }
            }
        }
    }
}

void timevalue_01_onTempoChanged(number tempo) {
    RNBO_UNUSED(tempo);

    {
        this->timevalue_01_sendValue();
    }
}

void timevalue_01_onSampleRateChanged(number ) {}

void timevalue_01_onTimeSignatureChanged(number numerator, number denominator) {
    {
        console->log("num: ", numerator, " den: ", denominator);
        this->timevalue_01_sendValue();
    }
}

number globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    number diffInBeats = diff * this->globaltransport_getTempo(time) * 0.008 / (number)480;
    return beatTimeBase + diffInBeats;
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample((SampleIndex)(offset)) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        SampleIndex offset = (SampleIndex)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_state, this->vs, state, (Index)(offset));
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;

        if (rnbo_abs(beattime - this->globaltransport_getBeatTime(time)) > 0.001) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = (MillisecondTime)(this->sampstoms(sampleOffset));
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

void globaltransport_setBBUBase(
    MillisecondTime time,
    number numerator,
    number denominator,
    number bars,
    number beats,
    number units
) {
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    bars--;
    beats--;
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;

    while (units > beatLengthInUnits) {
        units -= beatLengthInUnits;
        beats++;
    }

    number targetBeatTime = bars * numerator + beats + units / beatLengthInUnits;
    this->globaltransport_bbuBase = targetBeatTime - beatsIncCurrenttDenom;
}

array<number, 3> globaltransport_getBBU(MillisecondTime time) {
    array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);
    number numerator = currentSig[0];
    number denominator = currentSig[1];
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;
    number targetBeatTime = beatsIncCurrenttDenom + this->globaltransport_bbuBase;
    number currentBars = 0;
    number currentBeats = 0;
    number currentUnits = 0;

    if (targetBeatTime >= 0) {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;
        currentBeats = trunc(targetBeatTime);
        targetBeatTime -= currentBeats;
        currentUnits = targetBeatTime * beatLengthInUnits;
    } else {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;

        if (targetBeatTime != 0) {
            currentBars -= 1;
            currentBeats = trunc(targetBeatTime);
            targetBeatTime -= currentBeats;
            currentBeats = numerator + currentBeats;
            currentUnits = targetBeatTime * beatLengthInUnits;

            if (currentUnits != 0) {
                currentUnits = beatLengthInUnits + currentUnits;
                currentBeats -= 1;
            }
        }
    }

    return {currentBars + 1, currentBeats + 1, currentUnits};
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (Int)(numerator), (Int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            array<number, 3> bbu = this->globaltransport_getBBU(time);
            this->globaltransport_setBBUBase(time, numerator, denominator, bbu[0], bbu[1], bbu[2]);
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

array<number, 3> globaltransport_getBBUAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBBU(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setBBU(MillisecondTime time, number bars, number beats, number units, bool notify) {
    RNBO_UNUSED(notify);
    array<number, 2> sig = this->globaltransport_getTimeSignature(time);
    number numerator = sig[0];
    number denominator = sig[1];
    this->globaltransport_setBBUBase(time, numerator, denominator, bars, beats, units);
    return true;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (Int)(this->globaltransport_timeSignatureChanges[0]),
                (Int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

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
    delta_tilde_01_x = 0;
    phasor_01_freq = 0;
    param_01_value = 0;
    transport_01_input_number = 0;
    transport_01_position = 0;
    transport_01_tempo = 120;
    transport_01_ticks = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    param_02_value = 16;
    subdivobject_01_syncupdate = 0;
    subdivobject_01_lockprob = true;
    subdivobject_01_silentmode = false;
    subdivobject_01_div = 1;
    subdivobject_01_input_number = 0;
    subdivobject_01_stepmessage = 0;
    delta_tilde_02_x = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    param_03_value = 16;
    subdivobject_02_syncupdate = 0;
    subdivobject_02_lockprob = true;
    subdivobject_02_silentmode = false;
    subdivobject_02_div = 1;
    subdivobject_02_input_number = 0;
    subdivobject_02_stepmessage = 0;
    delta_tilde_03_x = 0;
    param_04_value = 120;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    param_05_value = 16;
    subdivobject_03_syncupdate = 0;
    subdivobject_03_lockprob = true;
    subdivobject_03_silentmode = false;
    subdivobject_03_div = 1;
    subdivobject_03_input_number = 0;
    subdivobject_03_stepmessage = 0;
    delta_tilde_04_x = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0;
    param_06_value = 16;
    subdivobject_04_syncupdate = 0;
    subdivobject_04_lockprob = true;
    subdivobject_04_silentmode = false;
    subdivobject_04_div = 1;
    subdivobject_04_input_number = 0;
    subdivobject_04_stepmessage = 0;
    delta_tilde_05_x = 0;
    dspexpr_06_in1 = 0;
    dspexpr_06_in2 = 0;
    param_07_value = 16;
    subdivobject_05_syncupdate = 0;
    subdivobject_05_lockprob = true;
    subdivobject_05_silentmode = false;
    subdivobject_05_div = 1;
    subdivobject_05_input_number = 0;
    subdivobject_05_stepmessage = 0;
    delta_tilde_06_x = 0;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    param_08_value = 16;
    subdivobject_06_syncupdate = 0;
    subdivobject_06_lockprob = true;
    subdivobject_06_silentmode = false;
    subdivobject_06_div = 1;
    subdivobject_06_input_number = 0;
    subdivobject_06_stepmessage = 0;
    delta_tilde_07_x = 0;
    dspexpr_08_in1 = 0;
    dspexpr_08_in2 = 0;
    param_09_value = 16;
    subdivobject_07_syncupdate = 0;
    subdivobject_07_lockprob = true;
    subdivobject_07_silentmode = false;
    subdivobject_07_div = 1;
    subdivobject_07_input_number = 0;
    subdivobject_07_stepmessage = 0;
    delta_tilde_08_x = 0;
    dspexpr_09_in1 = 0;
    dspexpr_09_in2 = 0;
    param_10_value = 16;
    subdivobject_08_syncupdate = 0;
    subdivobject_08_lockprob = true;
    subdivobject_08_silentmode = false;
    subdivobject_08_div = 1;
    subdivobject_08_input_number = 0;
    subdivobject_08_stepmessage = 0;
    delta_tilde_09_x = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    delta_tilde_01_prev = 0;
    delta_tilde_01_setupDone = false;
    phasor_01_sigbuf = nullptr;
    phasor_01_lastLockedPhase = 0;
    phasor_01_lastQuantum = 0;
    phasor_01_lastTempo = 0;
    phasor_01_nextJumpInSamples = 0;
    phasor_01_inc = 0;
    phasor_01_recalcInc = true;
    phasor_01_recalcPhase = true;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    subdivobject_01_subdivider_div = 1;
    subdivobject_01_subdivider_nextdiv = 1;
    subdivobject_01_subdivider_posstep = 0;
    subdivobject_01_subdivider_nextposstep = 0;
    subdivobject_01_subdivider_outstep = 0;
    subdivobject_01_subdivider_nextoutstep = 0;
    subdivobject_01_subdivider_prev = 0;
    subdivobject_01_subdivider_prev2 = 0;
    subdivobject_01_subdivider_playing = true;
    subdivobject_01_subdivider_lockprob = true;
    subdivobject_01_setupDone = false;
    delta_tilde_02_prev = 0;
    delta_tilde_02_setupDone = false;
    param_03_lastValue = 0;
    subdivobject_02_subdivider_div = 1;
    subdivobject_02_subdivider_nextdiv = 1;
    subdivobject_02_subdivider_posstep = 0;
    subdivobject_02_subdivider_nextposstep = 0;
    subdivobject_02_subdivider_outstep = 0;
    subdivobject_02_subdivider_nextoutstep = 0;
    subdivobject_02_subdivider_prev = 0;
    subdivobject_02_subdivider_prev2 = 0;
    subdivobject_02_subdivider_playing = true;
    subdivobject_02_subdivider_lockprob = true;
    subdivobject_02_setupDone = false;
    delta_tilde_03_prev = 0;
    delta_tilde_03_setupDone = false;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    subdivobject_03_subdivider_div = 1;
    subdivobject_03_subdivider_nextdiv = 1;
    subdivobject_03_subdivider_posstep = 0;
    subdivobject_03_subdivider_nextposstep = 0;
    subdivobject_03_subdivider_outstep = 0;
    subdivobject_03_subdivider_nextoutstep = 0;
    subdivobject_03_subdivider_prev = 0;
    subdivobject_03_subdivider_prev2 = 0;
    subdivobject_03_subdivider_playing = true;
    subdivobject_03_subdivider_lockprob = true;
    subdivobject_03_setupDone = false;
    delta_tilde_04_prev = 0;
    delta_tilde_04_setupDone = false;
    param_06_lastValue = 0;
    subdivobject_04_subdivider_div = 1;
    subdivobject_04_subdivider_nextdiv = 1;
    subdivobject_04_subdivider_posstep = 0;
    subdivobject_04_subdivider_nextposstep = 0;
    subdivobject_04_subdivider_outstep = 0;
    subdivobject_04_subdivider_nextoutstep = 0;
    subdivobject_04_subdivider_prev = 0;
    subdivobject_04_subdivider_prev2 = 0;
    subdivobject_04_subdivider_playing = true;
    subdivobject_04_subdivider_lockprob = true;
    subdivobject_04_setupDone = false;
    delta_tilde_05_prev = 0;
    delta_tilde_05_setupDone = false;
    param_07_lastValue = 0;
    subdivobject_05_subdivider_div = 1;
    subdivobject_05_subdivider_nextdiv = 1;
    subdivobject_05_subdivider_posstep = 0;
    subdivobject_05_subdivider_nextposstep = 0;
    subdivobject_05_subdivider_outstep = 0;
    subdivobject_05_subdivider_nextoutstep = 0;
    subdivobject_05_subdivider_prev = 0;
    subdivobject_05_subdivider_prev2 = 0;
    subdivobject_05_subdivider_playing = true;
    subdivobject_05_subdivider_lockprob = true;
    subdivobject_05_setupDone = false;
    delta_tilde_06_prev = 0;
    delta_tilde_06_setupDone = false;
    param_08_lastValue = 0;
    subdivobject_06_subdivider_div = 1;
    subdivobject_06_subdivider_nextdiv = 1;
    subdivobject_06_subdivider_posstep = 0;
    subdivobject_06_subdivider_nextposstep = 0;
    subdivobject_06_subdivider_outstep = 0;
    subdivobject_06_subdivider_nextoutstep = 0;
    subdivobject_06_subdivider_prev = 0;
    subdivobject_06_subdivider_prev2 = 0;
    subdivobject_06_subdivider_playing = true;
    subdivobject_06_subdivider_lockprob = true;
    subdivobject_06_setupDone = false;
    delta_tilde_07_prev = 0;
    delta_tilde_07_setupDone = false;
    param_09_lastValue = 0;
    subdivobject_07_subdivider_div = 1;
    subdivobject_07_subdivider_nextdiv = 1;
    subdivobject_07_subdivider_posstep = 0;
    subdivobject_07_subdivider_nextposstep = 0;
    subdivobject_07_subdivider_outstep = 0;
    subdivobject_07_subdivider_nextoutstep = 0;
    subdivobject_07_subdivider_prev = 0;
    subdivobject_07_subdivider_prev2 = 0;
    subdivobject_07_subdivider_playing = true;
    subdivobject_07_subdivider_lockprob = true;
    subdivobject_07_setupDone = false;
    delta_tilde_08_prev = 0;
    delta_tilde_08_setupDone = false;
    param_10_lastValue = 0;
    subdivobject_08_subdivider_div = 1;
    subdivobject_08_subdivider_nextdiv = 1;
    subdivobject_08_subdivider_posstep = 0;
    subdivobject_08_subdivider_nextposstep = 0;
    subdivobject_08_subdivider_outstep = 0;
    subdivobject_08_subdivider_nextoutstep = 0;
    subdivobject_08_subdivider_prev = 0;
    subdivobject_08_subdivider_prev2 = 0;
    subdivobject_08_subdivider_playing = true;
    subdivobject_08_subdivider_lockprob = true;
    subdivobject_08_setupDone = false;
    delta_tilde_09_prev = 0;
    delta_tilde_09_setupDone = false;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_bbuBase = 0;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number delta_tilde_01_x;
    number phasor_01_freq;
    number param_01_value;
    number transport_01_input_number;
    number transport_01_position;
    number transport_01_tempo;
    list transport_01_timesig;
    number transport_01_ticks;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number param_02_value;
    Int subdivobject_01_syncupdate;
    number subdivobject_01_lockprob;
    number subdivobject_01_silentmode;
    number subdivobject_01_div;
    number subdivobject_01_input_number;
    number subdivobject_01_stepmessage;
    number delta_tilde_02_x;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number param_03_value;
    Int subdivobject_02_syncupdate;
    number subdivobject_02_lockprob;
    number subdivobject_02_silentmode;
    number subdivobject_02_div;
    number subdivobject_02_input_number;
    number subdivobject_02_stepmessage;
    number delta_tilde_03_x;
    number param_04_value;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number param_05_value;
    Int subdivobject_03_syncupdate;
    number subdivobject_03_lockprob;
    number subdivobject_03_silentmode;
    number subdivobject_03_div;
    number subdivobject_03_input_number;
    number subdivobject_03_stepmessage;
    number delta_tilde_04_x;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number param_06_value;
    Int subdivobject_04_syncupdate;
    number subdivobject_04_lockprob;
    number subdivobject_04_silentmode;
    number subdivobject_04_div;
    number subdivobject_04_input_number;
    number subdivobject_04_stepmessage;
    number delta_tilde_05_x;
    number dspexpr_06_in1;
    number dspexpr_06_in2;
    number param_07_value;
    Int subdivobject_05_syncupdate;
    number subdivobject_05_lockprob;
    number subdivobject_05_silentmode;
    number subdivobject_05_div;
    number subdivobject_05_input_number;
    number subdivobject_05_stepmessage;
    number delta_tilde_06_x;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number param_08_value;
    Int subdivobject_06_syncupdate;
    number subdivobject_06_lockprob;
    number subdivobject_06_silentmode;
    number subdivobject_06_div;
    number subdivobject_06_input_number;
    number subdivobject_06_stepmessage;
    number delta_tilde_07_x;
    number dspexpr_08_in1;
    number dspexpr_08_in2;
    number param_09_value;
    Int subdivobject_07_syncupdate;
    number subdivobject_07_lockprob;
    number subdivobject_07_silentmode;
    number subdivobject_07_div;
    number subdivobject_07_input_number;
    number subdivobject_07_stepmessage;
    number delta_tilde_08_x;
    number dspexpr_09_in1;
    number dspexpr_09_in2;
    number param_10_value;
    Int subdivobject_08_syncupdate;
    number subdivobject_08_lockprob;
    number subdivobject_08_silentmode;
    number subdivobject_08_div;
    number subdivobject_08_input_number;
    number subdivobject_08_stepmessage;
    number delta_tilde_09_x;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[3];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number delta_tilde_01_prev;
    bool delta_tilde_01_setupDone;
    signal phasor_01_sigbuf;
    number phasor_01_lastLockedPhase;
    number phasor_01_lastQuantum;
    number phasor_01_lastTempo;
    number phasor_01_nextJumpInSamples;
    number phasor_01_inc;
    bool phasor_01_recalcInc;
    bool phasor_01_recalcPhase;
    number param_01_lastValue;
    number param_02_lastValue;
    number subdivobject_01_subdivider_div;
    number subdivobject_01_subdivider_nextdiv;
    number subdivobject_01_subdivider_posstep;
    number subdivobject_01_subdivider_nextposstep;
    number subdivobject_01_subdivider_outstep;
    number subdivobject_01_subdivider_nextoutstep;
    number subdivobject_01_subdivider_lastoutstep;
    number subdivobject_01_subdivider_prev;
    number subdivobject_01_subdivider_prev2;
    list subdivobject_01_subdivider_p2;
    list subdivobject_01_subdivider_synco;
    list subdivobject_01_subdivider_p2prob;
    list subdivobject_01_subdivider_pattern;
    list subdivobject_01_subdivider_prob;
    number subdivobject_01_subdivider_p2length;
    bool subdivobject_01_subdivider_playing;
    number subdivobject_01_subdivider_num;
    number subdivobject_01_subdivider_patternphase;
    number subdivobject_01_subdivider_patternstep;
    number subdivobject_01_subdivider_probstep;
    bool subdivobject_01_subdivider_lockprob;
    bool subdivobject_01_setupDone;
    number delta_tilde_02_prev;
    bool delta_tilde_02_setupDone;
    number param_03_lastValue;
    number subdivobject_02_subdivider_div;
    number subdivobject_02_subdivider_nextdiv;
    number subdivobject_02_subdivider_posstep;
    number subdivobject_02_subdivider_nextposstep;
    number subdivobject_02_subdivider_outstep;
    number subdivobject_02_subdivider_nextoutstep;
    number subdivobject_02_subdivider_lastoutstep;
    number subdivobject_02_subdivider_prev;
    number subdivobject_02_subdivider_prev2;
    list subdivobject_02_subdivider_p2;
    list subdivobject_02_subdivider_synco;
    list subdivobject_02_subdivider_p2prob;
    list subdivobject_02_subdivider_pattern;
    list subdivobject_02_subdivider_prob;
    number subdivobject_02_subdivider_p2length;
    bool subdivobject_02_subdivider_playing;
    number subdivobject_02_subdivider_num;
    number subdivobject_02_subdivider_patternphase;
    number subdivobject_02_subdivider_patternstep;
    number subdivobject_02_subdivider_probstep;
    bool subdivobject_02_subdivider_lockprob;
    bool subdivobject_02_setupDone;
    number delta_tilde_03_prev;
    bool delta_tilde_03_setupDone;
    number param_04_lastValue;
    number param_05_lastValue;
    number subdivobject_03_subdivider_div;
    number subdivobject_03_subdivider_nextdiv;
    number subdivobject_03_subdivider_posstep;
    number subdivobject_03_subdivider_nextposstep;
    number subdivobject_03_subdivider_outstep;
    number subdivobject_03_subdivider_nextoutstep;
    number subdivobject_03_subdivider_lastoutstep;
    number subdivobject_03_subdivider_prev;
    number subdivobject_03_subdivider_prev2;
    list subdivobject_03_subdivider_p2;
    list subdivobject_03_subdivider_synco;
    list subdivobject_03_subdivider_p2prob;
    list subdivobject_03_subdivider_pattern;
    list subdivobject_03_subdivider_prob;
    number subdivobject_03_subdivider_p2length;
    bool subdivobject_03_subdivider_playing;
    number subdivobject_03_subdivider_num;
    number subdivobject_03_subdivider_patternphase;
    number subdivobject_03_subdivider_patternstep;
    number subdivobject_03_subdivider_probstep;
    bool subdivobject_03_subdivider_lockprob;
    bool subdivobject_03_setupDone;
    number delta_tilde_04_prev;
    bool delta_tilde_04_setupDone;
    number param_06_lastValue;
    number subdivobject_04_subdivider_div;
    number subdivobject_04_subdivider_nextdiv;
    number subdivobject_04_subdivider_posstep;
    number subdivobject_04_subdivider_nextposstep;
    number subdivobject_04_subdivider_outstep;
    number subdivobject_04_subdivider_nextoutstep;
    number subdivobject_04_subdivider_lastoutstep;
    number subdivobject_04_subdivider_prev;
    number subdivobject_04_subdivider_prev2;
    list subdivobject_04_subdivider_p2;
    list subdivobject_04_subdivider_synco;
    list subdivobject_04_subdivider_p2prob;
    list subdivobject_04_subdivider_pattern;
    list subdivobject_04_subdivider_prob;
    number subdivobject_04_subdivider_p2length;
    bool subdivobject_04_subdivider_playing;
    number subdivobject_04_subdivider_num;
    number subdivobject_04_subdivider_patternphase;
    number subdivobject_04_subdivider_patternstep;
    number subdivobject_04_subdivider_probstep;
    bool subdivobject_04_subdivider_lockprob;
    bool subdivobject_04_setupDone;
    number delta_tilde_05_prev;
    bool delta_tilde_05_setupDone;
    number param_07_lastValue;
    number subdivobject_05_subdivider_div;
    number subdivobject_05_subdivider_nextdiv;
    number subdivobject_05_subdivider_posstep;
    number subdivobject_05_subdivider_nextposstep;
    number subdivobject_05_subdivider_outstep;
    number subdivobject_05_subdivider_nextoutstep;
    number subdivobject_05_subdivider_lastoutstep;
    number subdivobject_05_subdivider_prev;
    number subdivobject_05_subdivider_prev2;
    list subdivobject_05_subdivider_p2;
    list subdivobject_05_subdivider_synco;
    list subdivobject_05_subdivider_p2prob;
    list subdivobject_05_subdivider_pattern;
    list subdivobject_05_subdivider_prob;
    number subdivobject_05_subdivider_p2length;
    bool subdivobject_05_subdivider_playing;
    number subdivobject_05_subdivider_num;
    number subdivobject_05_subdivider_patternphase;
    number subdivobject_05_subdivider_patternstep;
    number subdivobject_05_subdivider_probstep;
    bool subdivobject_05_subdivider_lockprob;
    bool subdivobject_05_setupDone;
    number delta_tilde_06_prev;
    bool delta_tilde_06_setupDone;
    number param_08_lastValue;
    number subdivobject_06_subdivider_div;
    number subdivobject_06_subdivider_nextdiv;
    number subdivobject_06_subdivider_posstep;
    number subdivobject_06_subdivider_nextposstep;
    number subdivobject_06_subdivider_outstep;
    number subdivobject_06_subdivider_nextoutstep;
    number subdivobject_06_subdivider_lastoutstep;
    number subdivobject_06_subdivider_prev;
    number subdivobject_06_subdivider_prev2;
    list subdivobject_06_subdivider_p2;
    list subdivobject_06_subdivider_synco;
    list subdivobject_06_subdivider_p2prob;
    list subdivobject_06_subdivider_pattern;
    list subdivobject_06_subdivider_prob;
    number subdivobject_06_subdivider_p2length;
    bool subdivobject_06_subdivider_playing;
    number subdivobject_06_subdivider_num;
    number subdivobject_06_subdivider_patternphase;
    number subdivobject_06_subdivider_patternstep;
    number subdivobject_06_subdivider_probstep;
    bool subdivobject_06_subdivider_lockprob;
    bool subdivobject_06_setupDone;
    number delta_tilde_07_prev;
    bool delta_tilde_07_setupDone;
    number param_09_lastValue;
    number subdivobject_07_subdivider_div;
    number subdivobject_07_subdivider_nextdiv;
    number subdivobject_07_subdivider_posstep;
    number subdivobject_07_subdivider_nextposstep;
    number subdivobject_07_subdivider_outstep;
    number subdivobject_07_subdivider_nextoutstep;
    number subdivobject_07_subdivider_lastoutstep;
    number subdivobject_07_subdivider_prev;
    number subdivobject_07_subdivider_prev2;
    list subdivobject_07_subdivider_p2;
    list subdivobject_07_subdivider_synco;
    list subdivobject_07_subdivider_p2prob;
    list subdivobject_07_subdivider_pattern;
    list subdivobject_07_subdivider_prob;
    number subdivobject_07_subdivider_p2length;
    bool subdivobject_07_subdivider_playing;
    number subdivobject_07_subdivider_num;
    number subdivobject_07_subdivider_patternphase;
    number subdivobject_07_subdivider_patternstep;
    number subdivobject_07_subdivider_probstep;
    bool subdivobject_07_subdivider_lockprob;
    bool subdivobject_07_setupDone;
    number delta_tilde_08_prev;
    bool delta_tilde_08_setupDone;
    number param_10_lastValue;
    number subdivobject_08_subdivider_div;
    number subdivobject_08_subdivider_nextdiv;
    number subdivobject_08_subdivider_posstep;
    number subdivobject_08_subdivider_nextposstep;
    number subdivobject_08_subdivider_outstep;
    number subdivobject_08_subdivider_nextoutstep;
    number subdivobject_08_subdivider_lastoutstep;
    number subdivobject_08_subdivider_prev;
    number subdivobject_08_subdivider_prev2;
    list subdivobject_08_subdivider_p2;
    list subdivobject_08_subdivider_synco;
    list subdivobject_08_subdivider_p2prob;
    list subdivobject_08_subdivider_pattern;
    list subdivobject_08_subdivider_prob;
    number subdivobject_08_subdivider_p2length;
    bool subdivobject_08_subdivider_playing;
    number subdivobject_08_subdivider_num;
    number subdivobject_08_subdivider_patternphase;
    number subdivobject_08_subdivider_patternstep;
    number subdivobject_08_subdivider_probstep;
    bool subdivobject_08_subdivider_lockprob;
    bool subdivobject_08_setupDone;
    number delta_tilde_09_prev;
    bool delta_tilde_09_setupDone;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    number globaltransport_bbuBase;
    bool globaltransport_setupDone;
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

