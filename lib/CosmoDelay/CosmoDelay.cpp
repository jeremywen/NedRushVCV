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
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->ip_01_perform(this->signals[0], n);
    this->dspexpr_02_perform(this->signals[0], this->dspexpr_02_in2, this->signals[1], n);
    this->ip_02_perform(this->signals[0], n);
    this->ip_03_perform(this->signals[2], n);
    this->ip_04_perform(this->signals[3], n);
    this->dspexpr_05_perform(this->signals[3], this->dspexpr_05_in2, this->signals[4], n);
    this->mstosamps_tilde_01_perform(this->mstosamps_tilde_01_ms, this->signals[3], n);
    this->onepole_tilde_01_perform(this->signals[3], this->onepole_tilde_01_freqInHz, this->signals[5], n);
    this->ip_05_perform(this->signals[3], n);
    this->ip_06_perform(this->signals[6], n);
    this->mstosamps_tilde_02_perform(this->mstosamps_tilde_02_ms, this->signals[7], n);
    this->onepole_tilde_02_perform(this->signals[7], this->onepole_tilde_02_freqInHz, this->signals[8], n);
    this->feedbackreader_01_perform(this->signals[7], n);
    this->signaladder_01_perform(in2, this->signals[7], this->signals[7], n);
    this->delaytilde_01_perform(this->signals[5], this->signals[7], this->signals[9], n);
    this->signaladder_02_perform(this->signals[9], in2, out2, n);
    this->dspexpr_01_perform(this->signals[9], this->dspexpr_01_in2, this->signals[5], n);

    this->svf_tilde_01_perform(
        this->signals[5],
        this->signals[0],
        this->signals[2],
        this->signals[9],
        this->signals[10],
        this->signals[11],
        this->signals[12],
        n
    );

    this->selector_01_perform(
        this->signals[1],
        this->signals[9],
        this->signals[10],
        this->signals[11],
        this->signals[12],
        this->signals[2],
        n
    );

    this->dspexpr_04_perform(this->signals[2], this->signals[12], n);
    this->feedbackwriter_01_perform(this->signals[12], n);
    this->feedbackreader_02_perform(this->signals[12], n);
    this->signaladder_03_perform(in1, this->signals[12], this->signals[12], n);
    this->delaytilde_02_perform(this->signals[8], this->signals[12], this->signals[2], n);
    this->dspexpr_03_perform(this->signals[2], this->dspexpr_03_in2, this->signals[8], n);

    this->svf_tilde_02_perform(
        this->signals[8],
        this->signals[3],
        this->signals[6],
        this->signals[11],
        this->signals[10],
        this->signals[9],
        this->signals[1],
        n
    );

    this->selector_02_perform(
        this->signals[4],
        this->signals[11],
        this->signals[10],
        this->signals[9],
        this->signals[1],
        this->signals[6],
        n
    );

    this->dspexpr_06_perform(this->signals[6], this->signals[1], n);
    this->feedbackwriter_02_perform(this->signals[1], n);
    this->signaladder_04_perform(this->signals[2], in1, out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 13; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
        this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
        this->ip_03_sigbuf = resizeSignal(this->ip_03_sigbuf, this->maxvs, maxBlockSize);
        this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
        this->ip_04_sigbuf = resizeSignal(this->ip_04_sigbuf, this->maxvs, maxBlockSize);
        this->ip_05_sigbuf = resizeSignal(this->ip_05_sigbuf, this->maxvs, maxBlockSize);
        this->ip_06_sigbuf = resizeSignal(this->ip_06_sigbuf, this->maxvs, maxBlockSize);
        this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
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

    this->ip_01_dspsetup(forceDSPSetup);
    this->ip_02_dspsetup(forceDSPSetup);
    this->ip_03_dspsetup(forceDSPSetup);
    this->ip_04_dspsetup(forceDSPSetup);
    this->onepole_tilde_01_dspsetup(forceDSPSetup);
    this->ip_05_dspsetup(forceDSPSetup);
    this->ip_06_dspsetup(forceDSPSetup);
    this->onepole_tilde_02_dspsetup(forceDSPSetup);
    this->delaytilde_01_dspsetup(forceDSPSetup);
    this->svf_tilde_01_dspsetup(forceDSPSetup);
    this->delaytilde_02_dspsetup(forceDSPSetup);
    this->svf_tilde_02_dspsetup(forceDSPSetup);
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
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->delaytilde_01_del_bufferobj);
        break;
        }
    case 1:
        {
        return addressOf(this->delaytilde_02_del_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->delaytilde_01_del_buffer = reInitDataView(this->delaytilde_01_del_buffer, this->delaytilde_01_del_bufferobj);
    }

    if (index == 1) {
        this->delaytilde_02_del_buffer = reInitDataView(this->delaytilde_02_del_buffer, this->delaytilde_02_del_bufferobj);
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->delaytilde_01_del_bufferobj = initDataRef(
        this->delaytilde_01_del_bufferobj,
        this->dataRefStrings->name0,
        true,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->delaytilde_02_del_bufferobj = initDataRef(
        this->delaytilde_02_del_bufferobj,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->assign_defaults();
    this->applyState();
    this->delaytilde_01_del_bufferobj->setIndex(0);
    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    this->delaytilde_02_del_bufferobj->setIndex(1);
    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "filtertype"));
    this->param_02_getPresetValue(getSubState(preset, "feedback"));
    this->param_03_getPresetValue(getSubState(preset, "feedres"));
    this->param_04_getPresetValue(getSubState(preset, "feedfreq"));
    this->param_05_getPresetValue(getSubState(preset, "time"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->param_01_setPresetValue(getSubState(preset, "filtertype"));
    this->param_02_setPresetValue(getSubState(preset, "feedback"));
    this->param_03_setPresetValue(getSubState(preset, "feedres"));
    this->param_04_setPresetValue(getSubState(preset, "feedfreq"));
    this->param_05_setPresetValue(getSubState(preset, "time"));
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
    return 5;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "filtertype";
        }
    case 1:
        {
        return "feedback";
        }
    case 2:
        {
        return "feedres";
        }
    case 3:
        {
        return "feedfreq";
        }
    case 4:
        {
        return "time";
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
        return "filtertype";
        }
    case 1:
        {
        return "feedback";
        }
    case 2:
        {
        return "feedres";
        }
    case 3:
        {
        return "feedfreq";
        }
    case 4:
        {
        return "time";
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
            info->max = 3;
            info->exponent = 1;
            info->steps = 4;
            static const char * eVal0[] = {"lp", "hp", "bp", "notch"};
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
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 0.999;
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
            info->min = 0;
            info->max = 0.9;
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
            info->initialValue = 10000;
            info->min = 10;
            info->max = 10000;
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
            info->initialValue = 500;
            info->min = 1;
            info->max = 1000;
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
        {
        {
            value = (value < 0 ? 0 : (value > 3 ? 3 : value));
            ParameterValue normalizedValue = (value - 0) / (3 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 4);
            }

            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 0.999 ? 0.999 : value));
            ParameterValue normalizedValue = (value - 0) / (0.999 - 0);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 0.9 ? 0.9 : value));
            ParameterValue normalizedValue = (value - 0) / (0.9 - 0);
            return normalizedValue;
        }
        }
    case 4:
        {
        {
            value = (value < 1 ? 1 : (value > 1000 ? 1000 : value));
            ParameterValue normalizedValue = (value - 1) / (1000 - 1);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 10 ? 10 : (value > 10000 ? 10000 : value));
            ParameterValue normalizedValue = (value - 10) / (10000 - 10);
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
                value = this->applyStepsToNormalizedParameterValue(value, 4);
            }

            {
                return 0 + value * (3 - 0);
            }
        }
        }
    case 1:
        {
        {
            {
                return 0 + value * (0.999 - 0);
            }
        }
        }
    case 2:
        {
        {
            {
                return 0 + value * (0.9 - 0);
            }
        }
        }
    case 4:
        {
        {
            {
                return 1 + value * (1000 - 1);
            }
        }
        }
    case 3:
        {
        {
            {
                return 10 + value * (10000 - 10);
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

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
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

    this->ip_04_value_set(v);
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

    this->dspexpr_03_in2_set(v);
    this->dspexpr_01_in2_set(v);
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

    this->ip_06_value_set(v);
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

    this->ip_05_value_set(v);
    this->ip_02_value_set(v);
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

    this->mstosamps_tilde_02_ms_set(v);
    this->mstosamps_tilde_01_ms_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 13; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->ip_01_sigbuf = freeSignal(this->ip_01_sigbuf);
    this->ip_02_sigbuf = freeSignal(this->ip_02_sigbuf);
    this->ip_03_sigbuf = freeSignal(this->ip_03_sigbuf);
    this->feedbacktilde_01_feedbackbuffer = freeSignal(this->feedbacktilde_01_feedbackbuffer);
    this->ip_04_sigbuf = freeSignal(this->ip_04_sigbuf);
    this->ip_05_sigbuf = freeSignal(this->ip_05_sigbuf);
    this->ip_06_sigbuf = freeSignal(this->ip_06_sigbuf);
    this->feedbacktilde_02_feedbackbuffer = freeSignal(this->feedbacktilde_02_feedbackbuffer);
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

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void allocateDataRefs() {
    this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();

    if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_01_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_01_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();

    if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_02_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_02_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->ip_01_init();
    this->ip_02_init();
    this->ip_03_init();
    this->delaytilde_01_del_init();
    this->ip_04_init();
    this->ip_05_init();
    this->ip_06_init();
    this->delaytilde_02_del_init();
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

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 3 ? 3 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)3 / (number)3;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void ip_04_value_set(number v) {
    this->ip_04_value = v;
    this->ip_04_fillSigBuf();
    this->ip_04_lastValue = v;
}

void ip_01_value_set(number v) {
    this->ip_01_value = v;
    this->ip_01_fillSigBuf();
    this->ip_01_lastValue = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 0.999 ? 0.999 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_03_in2_set(number v) {
    this->dspexpr_03_in2 = v;
}

void dspexpr_01_in2_set(number v) {
    this->dspexpr_01_in2 = v;
}

number param_03_value_constrain(number v) const {
    v = (v > 0.9 ? 0.9 : (v < 0 ? 0 : v));
    return v;
}

void ip_06_value_set(number v) {
    this->ip_06_value = v;
    this->ip_06_fillSigBuf();
    this->ip_06_lastValue = v;
}

void ip_03_value_set(number v) {
    this->ip_03_value = v;
    this->ip_03_fillSigBuf();
    this->ip_03_lastValue = v;
}

number param_04_value_constrain(number v) const {
    v = (v > 10000 ? 10000 : (v < 10 ? 10 : v));
    return v;
}

void ip_05_value_set(number v) {
    this->ip_05_value = v;
    this->ip_05_fillSigBuf();
    this->ip_05_lastValue = v;
}

void ip_02_value_set(number v) {
    this->ip_02_value = v;
    this->ip_02_fillSigBuf();
    this->ip_02_lastValue = v;
}

number param_05_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 1 ? 1 : v));
    return v;
}

void mstosamps_tilde_02_ms_set(number v) {
    this->mstosamps_tilde_02_ms = v;
}

void mstosamps_tilde_01_ms_set(number v) {
    this->mstosamps_tilde_01_ms = v;
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

void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + 1;//#map:_###_obj_###_:1
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

void ip_03_perform(SampleValue * out, Index n) {
    auto __ip_03_lastValue = this->ip_03_lastValue;
    auto __ip_03_lastIndex = this->ip_03_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_03_lastIndex ? __ip_03_lastValue : this->ip_03_sigbuf[(Index)i]);
    }

    __ip_03_lastIndex = 0;
    this->ip_03_lastIndex = __ip_03_lastIndex;
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

void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + 1;//#map:_###_obj_###_:1
    }
}

void mstosamps_tilde_01_perform(number ms, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = ms * this->sr * 0.001;
    }
}

void onepole_tilde_01_perform(const Sample * x, number freqInHz, SampleValue * out1, Index n) {
    RNBO_UNUSED(freqInHz);
    auto __onepole_tilde_01_lastY = this->onepole_tilde_01_lastY;
    auto __onepole_tilde_01_b1 = this->onepole_tilde_01_b1;
    auto __onepole_tilde_01_a0 = this->onepole_tilde_01_a0;
    auto __onepole_tilde_01_needsUpdate = this->onepole_tilde_01_needsUpdate;
    auto __onepole_tilde_01_freq = this->onepole_tilde_01_freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__onepole_tilde_01_freq != 10 || (bool)(__onepole_tilde_01_needsUpdate)) {
            __onepole_tilde_01_freq = 10;
            __onepole_tilde_01_a0 = 1 - rnbo_exp(-62.83185307179586 / this->sr);
            __onepole_tilde_01_a0 = (__onepole_tilde_01_a0 > 0.99999 ? 0.99999 : (__onepole_tilde_01_a0 < 0.00001 ? 0.00001 : __onepole_tilde_01_a0));
            __onepole_tilde_01_b1 = 1 - __onepole_tilde_01_a0;
            __onepole_tilde_01_needsUpdate = false;
        }

        __onepole_tilde_01_lastY = __onepole_tilde_01_a0 * x[(Index)i] + __onepole_tilde_01_b1 * __onepole_tilde_01_lastY;
        out1[(Index)i] = __onepole_tilde_01_lastY;
    }

    this->onepole_tilde_01_freq = __onepole_tilde_01_freq;
    this->onepole_tilde_01_needsUpdate = __onepole_tilde_01_needsUpdate;
    this->onepole_tilde_01_a0 = __onepole_tilde_01_a0;
    this->onepole_tilde_01_b1 = __onepole_tilde_01_b1;
    this->onepole_tilde_01_lastY = __onepole_tilde_01_lastY;
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

void ip_06_perform(SampleValue * out, Index n) {
    auto __ip_06_lastValue = this->ip_06_lastValue;
    auto __ip_06_lastIndex = this->ip_06_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_06_lastIndex ? __ip_06_lastValue : this->ip_06_sigbuf[(Index)i]);
    }

    __ip_06_lastIndex = 0;
    this->ip_06_lastIndex = __ip_06_lastIndex;
}

void mstosamps_tilde_02_perform(number ms, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = ms * this->sr * 0.001;
    }
}

void onepole_tilde_02_perform(const Sample * x, number freqInHz, SampleValue * out1, Index n) {
    RNBO_UNUSED(freqInHz);
    auto __onepole_tilde_02_lastY = this->onepole_tilde_02_lastY;
    auto __onepole_tilde_02_b1 = this->onepole_tilde_02_b1;
    auto __onepole_tilde_02_a0 = this->onepole_tilde_02_a0;
    auto __onepole_tilde_02_needsUpdate = this->onepole_tilde_02_needsUpdate;
    auto __onepole_tilde_02_freq = this->onepole_tilde_02_freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__onepole_tilde_02_freq != 10 || (bool)(__onepole_tilde_02_needsUpdate)) {
            __onepole_tilde_02_freq = 10;
            __onepole_tilde_02_a0 = 1 - rnbo_exp(-62.83185307179586 / this->sr);
            __onepole_tilde_02_a0 = (__onepole_tilde_02_a0 > 0.99999 ? 0.99999 : (__onepole_tilde_02_a0 < 0.00001 ? 0.00001 : __onepole_tilde_02_a0));
            __onepole_tilde_02_b1 = 1 - __onepole_tilde_02_a0;
            __onepole_tilde_02_needsUpdate = false;
        }

        __onepole_tilde_02_lastY = __onepole_tilde_02_a0 * x[(Index)i] + __onepole_tilde_02_b1 * __onepole_tilde_02_lastY;
        out1[(Index)i] = __onepole_tilde_02_lastY;
    }

    this->onepole_tilde_02_freq = __onepole_tilde_02_freq;
    this->onepole_tilde_02_needsUpdate = __onepole_tilde_02_needsUpdate;
    this->onepole_tilde_02_a0 = __onepole_tilde_02_a0;
    this->onepole_tilde_02_b1 = __onepole_tilde_02_b1;
    this->onepole_tilde_02_lastY = __onepole_tilde_02_lastY;
}

void feedbackreader_01_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void delaytilde_01_perform(
    const Sample * delay,
    const SampleValue * input,
    SampleValue * output,
    Index n
) {
    auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
    auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
    auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
    auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_01_lastDelay == -1) {
            __delaytilde_01_lastDelay = delay[(Index)i];
        }

        if (__delaytilde_01_ramp > 0) {
            number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
            __delaytilde_01_ramp--;
        } else {
            number effectiveDelay = delay[(Index)i];

            if (effectiveDelay != __delaytilde_01_lastDelay) {
                __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                __delaytilde_01_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                __delaytilde_01_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_01_del_write(input[(Index)i]);
        this->delaytilde_01_del_step();
    }

    this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
    this->delaytilde_01_ramp = __delaytilde_01_ramp;
    this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
}

void signaladder_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void svf_tilde_01_perform(
    const Sample * x,
    const Sample * freq,
    const Sample * q,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    Index n
) {
    auto __svf_tilde_01_high = this->svf_tilde_01_high;
    auto __svf_tilde_01_notch = this->svf_tilde_01_notch;
    auto __svf_tilde_01_band = this->svf_tilde_01_band;
    auto __svf_tilde_01_low = this->svf_tilde_01_low;
    auto __svf_tilde_01__q = this->svf_tilde_01__q;
    auto __svf_tilde_01__freq = this->svf_tilde_01__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (this->svf_tilde_01_dFreq_next(freq[(Index)i]) != 0) {
            __svf_tilde_01__freq = (freq[(Index)i] > this->sr * 0.25 ? this->sr * 0.25 : (freq[(Index)i] < 0.0 ? 0.0 : freq[(Index)i]));
            __svf_tilde_01__freq = rnbo_sin(6.28318530717958647692 * __svf_tilde_01__freq / this->sr);
            __svf_tilde_01__freq = (__svf_tilde_01__freq > 0.99 ? 0.99 : (__svf_tilde_01__freq < 0.001 ? 0.001 : __svf_tilde_01__freq));
        }

        if (this->svf_tilde_01_dQ_next(q[(Index)i]) != 0) {
            __svf_tilde_01__q = (1. - q[(Index)i]) * 1.2;
            __svf_tilde_01__q = __svf_tilde_01__q * __svf_tilde_01__q;
            __svf_tilde_01__q = (__svf_tilde_01__q > 0.99 ? 0.99 : (__svf_tilde_01__q < 0.001 ? 0.001 : __svf_tilde_01__q));
        }

        __svf_tilde_01_low += __svf_tilde_01__freq * __svf_tilde_01_band;
        __svf_tilde_01_notch = x[(Index)i] - __svf_tilde_01__q * __svf_tilde_01_band;
        __svf_tilde_01_high = __svf_tilde_01_notch - __svf_tilde_01_low;
        __svf_tilde_01_band += __svf_tilde_01__freq * __svf_tilde_01_high - __svf_tilde_01_band * __svf_tilde_01_band * __svf_tilde_01_band * 0.0001;
        array<number, 4> tmp = {0, 0, 0, 0};
        tmp[0] = __svf_tilde_01_low;
        tmp[1] = __svf_tilde_01_high;
        tmp[2] = __svf_tilde_01_band;
        tmp[3] = __svf_tilde_01_notch;
        out1[(Index)i] = tmp[0];
        out2[(Index)i] = tmp[1];
        out3[(Index)i] = tmp[2];
        out4[(Index)i] = tmp[3];
    }

    this->svf_tilde_01__freq = __svf_tilde_01__freq;
    this->svf_tilde_01__q = __svf_tilde_01__q;
    this->svf_tilde_01_low = __svf_tilde_01_low;
    this->svf_tilde_01_band = __svf_tilde_01_band;
    this->svf_tilde_01_notch = __svf_tilde_01_notch;
    this->svf_tilde_01_high = __svf_tilde_01_high;
}

void selector_01_perform(
    const Sample * onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff[(Index)i] >= 1 && onoff[(Index)i] < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff[(Index)i] >= 2 && onoff[(Index)i] < 3)
            out[(Index)i] = in2[(Index)i];
        else if (onoff[(Index)i] >= 3 && onoff[(Index)i] < 4)
            out[(Index)i] = in3[(Index)i];
        else if (onoff[(Index)i] >= 4 && onoff[(Index)i] < 5)
            out[(Index)i] = in4[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_04_perform(const Sample * in1, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = rnbo_tanh(in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void feedbackwriter_01_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void feedbackreader_02_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void signaladder_03_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void delaytilde_02_perform(
    const Sample * delay,
    const SampleValue * input,
    SampleValue * output,
    Index n
) {
    auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
    auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
    auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
    auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_02_lastDelay == -1) {
            __delaytilde_02_lastDelay = delay[(Index)i];
        }

        if (__delaytilde_02_ramp > 0) {
            number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
            output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
            __delaytilde_02_ramp--;
        } else {
            number effectiveDelay = delay[(Index)i];

            if (effectiveDelay != __delaytilde_02_lastDelay) {
                __delaytilde_02_ramp = __delaytilde_02_rampInSamples;
                __delaytilde_02_crossfadeDelay = __delaytilde_02_lastDelay;
                __delaytilde_02_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0);
                __delaytilde_02_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_02_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_02_del_write(input[(Index)i]);
        this->delaytilde_02_del_step();
    }

    this->delaytilde_02_lastDelay = __delaytilde_02_lastDelay;
    this->delaytilde_02_ramp = __delaytilde_02_ramp;
    this->delaytilde_02_crossfadeDelay = __delaytilde_02_crossfadeDelay;
}

void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void svf_tilde_02_perform(
    const Sample * x,
    const Sample * freq,
    const Sample * q,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    Index n
) {
    auto __svf_tilde_02_high = this->svf_tilde_02_high;
    auto __svf_tilde_02_notch = this->svf_tilde_02_notch;
    auto __svf_tilde_02_band = this->svf_tilde_02_band;
    auto __svf_tilde_02_low = this->svf_tilde_02_low;
    auto __svf_tilde_02__q = this->svf_tilde_02__q;
    auto __svf_tilde_02__freq = this->svf_tilde_02__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (this->svf_tilde_02_dFreq_next(freq[(Index)i]) != 0) {
            __svf_tilde_02__freq = (freq[(Index)i] > this->sr * 0.25 ? this->sr * 0.25 : (freq[(Index)i] < 0.0 ? 0.0 : freq[(Index)i]));
            __svf_tilde_02__freq = rnbo_sin(6.28318530717958647692 * __svf_tilde_02__freq / this->sr);
            __svf_tilde_02__freq = (__svf_tilde_02__freq > 0.99 ? 0.99 : (__svf_tilde_02__freq < 0.001 ? 0.001 : __svf_tilde_02__freq));
        }

        if (this->svf_tilde_02_dQ_next(q[(Index)i]) != 0) {
            __svf_tilde_02__q = (1. - q[(Index)i]) * 1.2;
            __svf_tilde_02__q = __svf_tilde_02__q * __svf_tilde_02__q;
            __svf_tilde_02__q = (__svf_tilde_02__q > 0.99 ? 0.99 : (__svf_tilde_02__q < 0.001 ? 0.001 : __svf_tilde_02__q));
        }

        __svf_tilde_02_low += __svf_tilde_02__freq * __svf_tilde_02_band;
        __svf_tilde_02_notch = x[(Index)i] - __svf_tilde_02__q * __svf_tilde_02_band;
        __svf_tilde_02_high = __svf_tilde_02_notch - __svf_tilde_02_low;
        __svf_tilde_02_band += __svf_tilde_02__freq * __svf_tilde_02_high - __svf_tilde_02_band * __svf_tilde_02_band * __svf_tilde_02_band * 0.0001;
        array<number, 4> tmp = {0, 0, 0, 0};
        tmp[0] = __svf_tilde_02_low;
        tmp[1] = __svf_tilde_02_high;
        tmp[2] = __svf_tilde_02_band;
        tmp[3] = __svf_tilde_02_notch;
        out1[(Index)i] = tmp[0];
        out2[(Index)i] = tmp[1];
        out3[(Index)i] = tmp[2];
        out4[(Index)i] = tmp[3];
    }

    this->svf_tilde_02__freq = __svf_tilde_02__freq;
    this->svf_tilde_02__q = __svf_tilde_02__q;
    this->svf_tilde_02_low = __svf_tilde_02_low;
    this->svf_tilde_02_band = __svf_tilde_02_band;
    this->svf_tilde_02_notch = __svf_tilde_02_notch;
    this->svf_tilde_02_high = __svf_tilde_02_high;
}

void selector_02_perform(
    const Sample * onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff[(Index)i] >= 1 && onoff[(Index)i] < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff[(Index)i] >= 2 && onoff[(Index)i] < 3)
            out[(Index)i] = in2[(Index)i];
        else if (onoff[(Index)i] >= 3 && onoff[(Index)i] < 4)
            out[(Index)i] = in3[(Index)i];
        else if (onoff[(Index)i] >= 4 && onoff[(Index)i] < 5)
            out[(Index)i] = in4[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_06_perform(const Sample * in1, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = rnbo_tanh(in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void feedbackwriter_02_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void signaladder_04_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
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

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

number svf_tilde_01_dFreq_next(number x) {
    number temp = (number)(x - this->svf_tilde_01_dFreq_prev);
    this->svf_tilde_01_dFreq_prev = x;
    return temp;
}

void svf_tilde_01_dFreq_dspsetup() {
    this->svf_tilde_01_dFreq_reset();
}

void svf_tilde_01_dFreq_reset() {
    this->svf_tilde_01_dFreq_prev = 0;
}

number svf_tilde_01_dQ_next(number x) {
    number temp = (number)(x - this->svf_tilde_01_dQ_prev);
    this->svf_tilde_01_dQ_prev = x;
    return temp;
}

void svf_tilde_01_dQ_dspsetup() {
    this->svf_tilde_01_dQ_reset();
}

void svf_tilde_01_dQ_reset() {
    this->svf_tilde_01_dQ_prev = 0;
}

void svf_tilde_01_reset() {
    this->svf_tilde_01_low = 0;
    this->svf_tilde_01_high = 0;
    this->svf_tilde_01_band = 0;
    this->svf_tilde_01_notch = 0;
    this->svf_tilde_01_dFreq_reset();
    this->svf_tilde_01_dQ_reset();
}

void svf_tilde_01_dspsetup(bool force) {
    if ((bool)(this->svf_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->svf_tilde_01_reset();
    this->svf_tilde_01_setupDone = true;
    this->svf_tilde_01_dFreq_dspsetup();
    this->svf_tilde_01_dQ_dspsetup();
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

void delaytilde_01_del_step() {
    this->delaytilde_01_del_reader++;

    if (this->delaytilde_01_del_reader >= (Int)(this->delaytilde_01_del_buffer->getSize()))
        this->delaytilde_01_del_reader = 0;
}

number delaytilde_01_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 6) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 7) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    }

    number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->delaytilde_01_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
    );
}

void delaytilde_01_del_write(number v) {
    this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
    this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
}

number delaytilde_01_del_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
    number val = this->delaytilde_01_del_read(effectiveSize, 0);
    this->delaytilde_01_del_write(v);
    this->delaytilde_01_del_step();
    return val;
}

array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->sr, this->vs);
        this->delaytilde_01_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_01_del_init() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_01_del_clear() {
    this->delaytilde_01_del_buffer->setZero();
}

void delaytilde_01_del_reset() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_01_del_buffer);
    this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
    this->delaytilde_01_del_clear();

    if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
        this->delaytilde_01_del_reader = 0;
        this->delaytilde_01_del_writer = 0;
    }
}

void delaytilde_01_del_dspsetup() {
    this->delaytilde_01_del_reset();
}

number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    return samplerate;
}

number delaytilde_01_del_size() {
    return this->delaytilde_01_del__maxdelay;
}

void delaytilde_01_dspsetup(bool force) {
    if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_01_rampInSamples = (Int)(this->mstosamps(50));
    this->delaytilde_01_lastDelay = -1;
    this->delaytilde_01_setupDone = true;
    this->delaytilde_01_del_dspsetup();
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

void onepole_tilde_01_reset() {
    this->onepole_tilde_01_lastY = 0;
    this->onepole_tilde_01_a0 = 0;
    this->onepole_tilde_01_b1 = 0;
}

void onepole_tilde_01_dspsetup(bool force) {
    if ((bool)(this->onepole_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->onepole_tilde_01_needsUpdate = true;
    this->onepole_tilde_01_reset();
    this->onepole_tilde_01_setupDone = true;
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

number svf_tilde_02_dFreq_next(number x) {
    number temp = (number)(x - this->svf_tilde_02_dFreq_prev);
    this->svf_tilde_02_dFreq_prev = x;
    return temp;
}

void svf_tilde_02_dFreq_dspsetup() {
    this->svf_tilde_02_dFreq_reset();
}

void svf_tilde_02_dFreq_reset() {
    this->svf_tilde_02_dFreq_prev = 0;
}

number svf_tilde_02_dQ_next(number x) {
    number temp = (number)(x - this->svf_tilde_02_dQ_prev);
    this->svf_tilde_02_dQ_prev = x;
    return temp;
}

void svf_tilde_02_dQ_dspsetup() {
    this->svf_tilde_02_dQ_reset();
}

void svf_tilde_02_dQ_reset() {
    this->svf_tilde_02_dQ_prev = 0;
}

void svf_tilde_02_reset() {
    this->svf_tilde_02_low = 0;
    this->svf_tilde_02_high = 0;
    this->svf_tilde_02_band = 0;
    this->svf_tilde_02_notch = 0;
    this->svf_tilde_02_dFreq_reset();
    this->svf_tilde_02_dQ_reset();
}

void svf_tilde_02_dspsetup(bool force) {
    if ((bool)(this->svf_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->svf_tilde_02_reset();
    this->svf_tilde_02_setupDone = true;
    this->svf_tilde_02_dFreq_dspsetup();
    this->svf_tilde_02_dQ_dspsetup();
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
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

void delaytilde_02_del_step() {
    this->delaytilde_02_del_reader++;

    if (this->delaytilde_02_del_reader >= (Int)(this->delaytilde_02_del_buffer->getSize()))
        this->delaytilde_02_del_reader = 0;
}

number delaytilde_02_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 6) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 7) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    }

    number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->delaytilde_02_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
    );
}

void delaytilde_02_del_write(number v) {
    this->delaytilde_02_del_writer = this->delaytilde_02_del_reader;
    this->delaytilde_02_del_buffer[(Index)this->delaytilde_02_del_writer] = v;
}

number delaytilde_02_del_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_02_del__maxdelay : size);
    number val = this->delaytilde_02_del_read(effectiveSize, 0);
    this->delaytilde_02_del_write(v);
    this->delaytilde_02_del_step();
    return val;
}

array<Index, 2> delaytilde_02_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_02_del_evaluateSizeExpr(this->sr, this->vs);
        this->delaytilde_02_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_02_del_init() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_02_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_02_del_clear() {
    this->delaytilde_02_del_buffer->setZero();
}

void delaytilde_02_del_reset() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_02_del_buffer);
    this->delaytilde_02_del_wrap = this->delaytilde_02_del_buffer->getSize() - 1;
    this->delaytilde_02_del_clear();

    if (this->delaytilde_02_del_reader >= this->delaytilde_02_del__maxdelay || this->delaytilde_02_del_writer >= this->delaytilde_02_del__maxdelay) {
        this->delaytilde_02_del_reader = 0;
        this->delaytilde_02_del_writer = 0;
    }
}

void delaytilde_02_del_dspsetup() {
    this->delaytilde_02_del_reset();
}

number delaytilde_02_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    return samplerate;
}

number delaytilde_02_del_size() {
    return this->delaytilde_02_del__maxdelay;
}

void delaytilde_02_dspsetup(bool force) {
    if ((bool)(this->delaytilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_02_rampInSamples = (Int)(this->mstosamps(50));
    this->delaytilde_02_lastDelay = -1;
    this->delaytilde_02_setupDone = true;
    this->delaytilde_02_del_dspsetup();
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void onepole_tilde_02_reset() {
    this->onepole_tilde_02_lastY = 0;
    this->onepole_tilde_02_a0 = 0;
    this->onepole_tilde_02_b1 = 0;
}

void onepole_tilde_02_dspsetup(bool force) {
    if ((bool)(this->onepole_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->onepole_tilde_02_needsUpdate = true;
    this->onepole_tilde_02_reset();
    this->onepole_tilde_02_setupDone = true;
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
    param_01_value = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0.5;
    param_02_value = 0.5;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 1;
    ip_01_value = 0;
    ip_01_impulse = 0;
    selector_01_onoff = 1;
    ip_02_value = 0;
    ip_02_impulse = 0;
    param_03_value = 0;
    svf_tilde_01_x = 0;
    svf_tilde_01_freq = 0;
    svf_tilde_01_q = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0.5;
    dspexpr_04_in1 = 0;
    ip_03_value = 0;
    ip_03_impulse = 0;
    delaytilde_01_delay = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 1;
    ip_04_value = 0;
    ip_04_impulse = 0;
    selector_02_onoff = 1;
    onepole_tilde_01_x = 0;
    onepole_tilde_01_freqInHz = 10;
    mstosamps_tilde_01_ms = 0;
    ip_05_value = 0;
    ip_05_impulse = 0;
    svf_tilde_02_x = 0;
    svf_tilde_02_freq = 0;
    svf_tilde_02_q = 0;
    param_04_value = 10000;
    dspexpr_06_in1 = 0;
    ip_06_value = 0;
    ip_06_impulse = 0;
    delaytilde_02_delay = 0;
    param_05_value = 500;
    onepole_tilde_02_x = 0;
    onepole_tilde_02_freqInHz = 10;
    mstosamps_tilde_02_ms = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    signals[6] = nullptr;
    signals[7] = nullptr;
    signals[8] = nullptr;
    signals[9] = nullptr;
    signals[10] = nullptr;
    signals[11] = nullptr;
    signals[12] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    ip_01_lastIndex = 0;
    ip_01_lastValue = 0;
    ip_01_resetCount = 0;
    ip_01_sigbuf = nullptr;
    ip_01_setupDone = false;
    ip_02_lastIndex = 0;
    ip_02_lastValue = 0;
    ip_02_resetCount = 0;
    ip_02_sigbuf = nullptr;
    ip_02_setupDone = false;
    param_03_lastValue = 0;
    svf_tilde_01_low = 0;
    svf_tilde_01_high = 0;
    svf_tilde_01_band = 0;
    svf_tilde_01_notch = 0;
    svf_tilde_01__freq = 0.001;
    svf_tilde_01__q = 0.001;
    svf_tilde_01_dFreq_prev = 0;
    svf_tilde_01_dQ_prev = 0;
    svf_tilde_01_setupDone = false;
    ip_03_lastIndex = 0;
    ip_03_lastValue = 0;
    ip_03_resetCount = 0;
    ip_03_sigbuf = nullptr;
    ip_03_setupDone = false;
    feedbacktilde_01_feedbackbuffer = nullptr;
    delaytilde_01_lastDelay = -1;
    delaytilde_01_crossfadeDelay = 0;
    delaytilde_01_ramp = 0;
    delaytilde_01_rampInSamples = 0;
    delaytilde_01_del__maxdelay = 0;
    delaytilde_01_del_sizemode = 0;
    delaytilde_01_del_wrap = 0;
    delaytilde_01_del_reader = 0;
    delaytilde_01_del_writer = 0;
    delaytilde_01_setupDone = false;
    ip_04_lastIndex = 0;
    ip_04_lastValue = 0;
    ip_04_resetCount = 0;
    ip_04_sigbuf = nullptr;
    ip_04_setupDone = false;
    onepole_tilde_01_freq = 0;
    onepole_tilde_01_needsUpdate = false;
    onepole_tilde_01_lastY = 0;
    onepole_tilde_01_a0 = 0;
    onepole_tilde_01_b1 = 0;
    onepole_tilde_01_setupDone = false;
    ip_05_lastIndex = 0;
    ip_05_lastValue = 0;
    ip_05_resetCount = 0;
    ip_05_sigbuf = nullptr;
    ip_05_setupDone = false;
    svf_tilde_02_low = 0;
    svf_tilde_02_high = 0;
    svf_tilde_02_band = 0;
    svf_tilde_02_notch = 0;
    svf_tilde_02__freq = 0.001;
    svf_tilde_02__q = 0.001;
    svf_tilde_02_dFreq_prev = 0;
    svf_tilde_02_dQ_prev = 0;
    svf_tilde_02_setupDone = false;
    param_04_lastValue = 0;
    ip_06_lastIndex = 0;
    ip_06_lastValue = 0;
    ip_06_resetCount = 0;
    ip_06_sigbuf = nullptr;
    ip_06_setupDone = false;
    feedbacktilde_02_feedbackbuffer = nullptr;
    delaytilde_02_lastDelay = -1;
    delaytilde_02_crossfadeDelay = 0;
    delaytilde_02_ramp = 0;
    delaytilde_02_rampInSamples = 0;
    delaytilde_02_del__maxdelay = 0;
    delaytilde_02_del_sizemode = 0;
    delaytilde_02_del_wrap = 0;
    delaytilde_02_del_reader = 0;
    delaytilde_02_del_writer = 0;
    delaytilde_02_setupDone = false;
    param_05_lastValue = 0;
    onepole_tilde_02_freq = 0;
    onepole_tilde_02_needsUpdate = false;
    onepole_tilde_02_lastY = 0;
    onepole_tilde_02_a0 = 0;
    onepole_tilde_02_b1 = 0;
    onepole_tilde_02_setupDone = false;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "delaytilde_01_del_bufferobj";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	static constexpr auto& name1 = "delaytilde_02_del_bufferobj";
    	static constexpr auto& file1 = "";
    	static constexpr auto& tag1 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number param_01_value;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number param_02_value;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number ip_01_value;
    number ip_01_impulse;
    number selector_01_onoff;
    number ip_02_value;
    number ip_02_impulse;
    number param_03_value;
    number svf_tilde_01_x;
    number svf_tilde_01_freq;
    number svf_tilde_01_q;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number dspexpr_04_in1;
    number ip_03_value;
    number ip_03_impulse;
    number delaytilde_01_delay;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number ip_04_value;
    number ip_04_impulse;
    number selector_02_onoff;
    number onepole_tilde_01_x;
    number onepole_tilde_01_freqInHz;
    number mstosamps_tilde_01_ms;
    number ip_05_value;
    number ip_05_impulse;
    number svf_tilde_02_x;
    number svf_tilde_02_freq;
    number svf_tilde_02_q;
    number param_04_value;
    number dspexpr_06_in1;
    number ip_06_value;
    number ip_06_impulse;
    number delaytilde_02_delay;
    number param_05_value;
    number onepole_tilde_02_x;
    number onepole_tilde_02_freqInHz;
    number mstosamps_tilde_02_ms;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[13];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    SampleIndex ip_01_lastIndex;
    number ip_01_lastValue;
    SampleIndex ip_01_resetCount;
    signal ip_01_sigbuf;
    bool ip_01_setupDone;
    SampleIndex ip_02_lastIndex;
    number ip_02_lastValue;
    SampleIndex ip_02_resetCount;
    signal ip_02_sigbuf;
    bool ip_02_setupDone;
    number param_03_lastValue;
    number svf_tilde_01_low;
    number svf_tilde_01_high;
    number svf_tilde_01_band;
    number svf_tilde_01_notch;
    number svf_tilde_01__freq;
    number svf_tilde_01__q;
    number svf_tilde_01_dFreq_prev;
    number svf_tilde_01_dQ_prev;
    bool svf_tilde_01_setupDone;
    SampleIndex ip_03_lastIndex;
    number ip_03_lastValue;
    SampleIndex ip_03_resetCount;
    signal ip_03_sigbuf;
    bool ip_03_setupDone;
    signal feedbacktilde_01_feedbackbuffer;
    number delaytilde_01_lastDelay;
    number delaytilde_01_crossfadeDelay;
    number delaytilde_01_ramp;
    Int delaytilde_01_rampInSamples;
    Float64BufferRef delaytilde_01_del_buffer;
    Index delaytilde_01_del__maxdelay;
    Int delaytilde_01_del_sizemode;
    Index delaytilde_01_del_wrap;
    Int delaytilde_01_del_reader;
    Int delaytilde_01_del_writer;
    bool delaytilde_01_setupDone;
    SampleIndex ip_04_lastIndex;
    number ip_04_lastValue;
    SampleIndex ip_04_resetCount;
    signal ip_04_sigbuf;
    bool ip_04_setupDone;
    number onepole_tilde_01_freq;
    bool onepole_tilde_01_needsUpdate;
    number onepole_tilde_01_lastY;
    number onepole_tilde_01_a0;
    number onepole_tilde_01_b1;
    bool onepole_tilde_01_setupDone;
    SampleIndex ip_05_lastIndex;
    number ip_05_lastValue;
    SampleIndex ip_05_resetCount;
    signal ip_05_sigbuf;
    bool ip_05_setupDone;
    number svf_tilde_02_low;
    number svf_tilde_02_high;
    number svf_tilde_02_band;
    number svf_tilde_02_notch;
    number svf_tilde_02__freq;
    number svf_tilde_02__q;
    number svf_tilde_02_dFreq_prev;
    number svf_tilde_02_dQ_prev;
    bool svf_tilde_02_setupDone;
    number param_04_lastValue;
    SampleIndex ip_06_lastIndex;
    number ip_06_lastValue;
    SampleIndex ip_06_resetCount;
    signal ip_06_sigbuf;
    bool ip_06_setupDone;
    signal feedbacktilde_02_feedbackbuffer;
    number delaytilde_02_lastDelay;
    number delaytilde_02_crossfadeDelay;
    number delaytilde_02_ramp;
    Int delaytilde_02_rampInSamples;
    Float64BufferRef delaytilde_02_del_buffer;
    Index delaytilde_02_del__maxdelay;
    Int delaytilde_02_del_sizemode;
    Index delaytilde_02_del_wrap;
    Int delaytilde_02_del_reader;
    Int delaytilde_02_del_writer;
    bool delaytilde_02_setupDone;
    number param_05_lastValue;
    number onepole_tilde_02_freq;
    bool onepole_tilde_02_needsUpdate;
    number onepole_tilde_02_lastY;
    number onepole_tilde_02_a0;
    number onepole_tilde_02_b1;
    bool onepole_tilde_02_setupDone;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef delaytilde_01_del_bufferobj;
    DataRef delaytilde_02_del_bufferobj;
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

