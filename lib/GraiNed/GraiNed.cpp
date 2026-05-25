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
    this->dspexpr_01_perform(this->signals[0], this->dspexpr_01_in2, this->signals[1], n);

    this->recordtilde_01_perform(
        this->recordtilde_01_record,
        this->recordtilde_01_begin,
        this->recordtilde_01_end,
        in1,
        in2,
        this->dummyBuffer,
        n
    );

    this->ip_02_perform(this->signals[0], n);
    this->ip_03_perform(this->signals[2], n);
    this->dspexpr_03_perform(this->signals[0], this->signals[2], this->signals[3], n);
    this->ip_04_perform(this->signals[2], n);
    this->ip_05_perform(this->signals[0], n);
    this->dspexpr_07_perform(this->signals[2], this->signals[0], this->signals[4], n);

    this->groove_01_perform(
        this->signals[3],
        this->signals[2],
        this->signals[4],
        this->signals[0],
        this->signals[5],
        this->signals[6],
        n
    );

    this->trapezoid_tilde_01_perform(
        this->signals[6],
        this->trapezoid_tilde_01_rampUp,
        this->trapezoid_tilde_01_rampDown,
        this->signals[4],
        n
    );

    this->dspexpr_05_perform(this->signals[4], this->dspexpr_05_in2, this->signals[6], n);
    this->dspexpr_06_perform(this->signals[6], this->signals[4], n);
    this->dspexpr_04_perform(this->signals[5], this->signals[4], this->signals[6], n);
    this->selector_02_perform(this->signals[1], in2, this->signals[6], out2, n);
    this->dspexpr_02_perform(this->signals[0], this->signals[4], this->signals[6], n);
    this->selector_01_perform(this->signals[1], in1, this->signals[6], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 7; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
        this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
        this->ip_03_sigbuf = resizeSignal(this->ip_03_sigbuf, this->maxvs, maxBlockSize);
        this->ip_04_sigbuf = resizeSignal(this->ip_04_sigbuf, this->maxvs, maxBlockSize);
        this->ip_05_sigbuf = resizeSignal(this->ip_05_sigbuf, this->maxvs, maxBlockSize);
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
    this->data_01_dspsetup(forceDSPSetup);
    this->ip_05_dspsetup(forceDSPSetup);
    this->groove_01_dspsetup(forceDSPSetup);
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
        return addressOf(this->grained);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->recordtilde_01_buffer = reInitDataView(this->recordtilde_01_buffer, this->grained);
        this->groove_01_buffer = reInitDataView(this->groove_01_buffer, this->grained);
        this->data_01_buffer = reInitDataView(this->data_01_buffer, this->grained);
        this->data_01_afterBufferUpdate();
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->grained = initDataRef(
        this->grained,
        this->dataRefStrings->name0,
        false,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->assign_defaults();
    this->applyState();
    this->grained->setIndex(0);
    this->recordtilde_01_buffer = new Float32Buffer(this->grained);
    this->groove_01_buffer = new Float32Buffer(this->grained);
    this->data_01_buffer = new Float32Buffer(this->grained);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "pitch"));
    this->param_02_getPresetValue(getSubState(preset, "go"));
    this->param_03_getPresetValue(getSubState(preset, "start"));
    this->param_04_getPresetValue(getSubState(preset, "length"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->param_01_setPresetValue(getSubState(preset, "pitch"));
    this->param_02_setPresetValue(getSubState(preset, "go"));
    this->param_03_setPresetValue(getSubState(preset, "start"));
    this->param_04_setPresetValue(getSubState(preset, "length"));
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
    return 4;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "pitch";
        }
    case 1:
        {
        return "go";
        }
    case 2:
        {
        return "start";
        }
    case 3:
        {
        return "length";
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
        return "pitch";
        }
    case 1:
        {
        return "go";
        }
    case 2:
        {
        return "start";
        }
    case 3:
        {
        return "length";
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
            info->min = -4;
            info->max = 4;
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal1[] = {"0", "1"};
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
            info->initialValue = 0;
            info->min = 0;
            info->max = 1500;
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
            info->initialValue = 100;
            info->min = 1;
            info->max = 500;
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
    case 1:
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
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1500 ? 1500 : value));
            ParameterValue normalizedValue = (value - 0) / (1500 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 1 ? 1 : (value > 500 ? 500 : value));
            ParameterValue normalizedValue = (value - 1) / (500 - 1);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < -4 ? -4 : (value > 4 ? 4 : value));
            ParameterValue normalizedValue = (value - -4) / (4 - -4);
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
    case 1:
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
    case 2:
        {
        {
            {
                return 0 + value * (1500 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return 1 + value * (500 - 1);
            }
        }
        }
    case 0:
        {
        {
            {
                return -4 + value * (4 - -4);
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

number minimum(number x, number y) {
    return (y < x ? y : x);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    Int numWraps = (Int)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
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

    this->ip_03_value_set(v);
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

    this->recordtilde_01_record_set(v);
    this->select_01_input_number_set(v);
    this->ip_01_value_set(v);
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

    this->ip_04_value_set(v);
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
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 7; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->ip_01_sigbuf = freeSignal(this->ip_01_sigbuf);
    this->ip_02_sigbuf = freeSignal(this->ip_02_sigbuf);
    this->ip_03_sigbuf = freeSignal(this->ip_03_sigbuf);
    this->ip_04_sigbuf = freeSignal(this->ip_04_sigbuf);
    this->ip_05_sigbuf = freeSignal(this->ip_05_sigbuf);
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
    this->data_01_buffer->requestSize(this->mstosamps(2000), 2);
    this->data_01_buffer->setSampleRate(this->sr);
    this->recordtilde_01_buffer = this->recordtilde_01_buffer->allocateIfNeeded();
    this->groove_01_buffer = this->groove_01_buffer->allocateIfNeeded();
    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->grained->hasRequestedSize()) {
        if (this->grained->wantsFill())
            this->zeroDataRef(this->grained);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->ip_01_init();
    this->ip_02_init();
    this->ip_03_init();
    this->ip_04_init();
    this->data_01_init();
    this->ip_05_init();
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

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 4 ? 4 : (v < -4 ? -4 : v));
    return v;
}

void ip_03_value_set(number v) {
    this->ip_03_value = v;
    this->ip_03_fillSigBuf();
    this->ip_03_lastValue = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void recordtilde_01_record_set(number v) {
    this->recordtilde_01_record = v;

    if ((bool)(v)) {
        this->recordtilde_01_lastRecord = 0;
    }
}

void groove_01_rate_bang_bang() {
    this->groove_01_changeIncomingInSamples = this->sampleOffsetIntoNextAudioBuffer + 1;
    this->groove_01_incomingChange = 1;
}

void select_01_match1_bang() {
    this->groove_01_rate_bang_bang();
}

void select_01_nomatch_number_set(number ) {}

void select_01_input_number_set(number v) {
    if (v == this->select_01_test1)
        this->select_01_match1_bang();
    else
        this->select_01_nomatch_number_set(v);
}

void ip_01_value_set(number v) {
    this->ip_01_value = v;
    this->ip_01_fillSigBuf();
    this->ip_01_lastValue = v;
}

number param_03_value_constrain(number v) const {
    v = (v > 1500 ? 1500 : (v < 0 ? 0 : v));
    return v;
}

void ip_04_value_set(number v) {
    this->ip_04_value = v;
    this->ip_04_fillSigBuf();
    this->ip_04_lastValue = v;
}

number param_04_value_constrain(number v) const {
    v = (v > 500 ? 500 : (v < 1 ? 1 : v));
    return v;
}

void ip_05_value_set(number v) {
    this->ip_05_value = v;
    this->ip_05_fillSigBuf();
    this->ip_05_lastValue = v;
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

void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + 1;//#map:_###_obj_###_:1
    }
}

void recordtilde_01_perform(
    number record,
    number begin,
    number end,
    const SampleValue * input1,
    const SampleValue * input2,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(input2);
    RNBO_UNUSED(input1);
    RNBO_UNUSED(end);
    RNBO_UNUSED(begin);
    auto __recordtilde_01_loop = this->recordtilde_01_loop;
    auto __recordtilde_01_wIndex = this->recordtilde_01_wIndex;
    auto __recordtilde_01_lastRecord = this->recordtilde_01_lastRecord;
    auto __recordtilde_01_append = this->recordtilde_01_append;
    auto __recordtilde_01_buffer = this->recordtilde_01_buffer;
    ConstSampleArray<2> input = {input1, input2};
    number bufferSize = __recordtilde_01_buffer->getSize();
    number srInv = (number)1 / this->sr;

    if (bufferSize > 0) {
        number maxChannel = __recordtilde_01_buffer->getChannels();
        number touched = false;

        for (Index i = 0; i < n; i++) {
            number loopBegin = 0;
            number loopEnd = bufferSize;

            if (loopEnd > loopBegin) {
                if ((bool)(__recordtilde_01_append)) {
                    if ((bool)(record) && __recordtilde_01_lastRecord != record && __recordtilde_01_wIndex >= loopEnd) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                } else {
                    if ((bool)(record) && __recordtilde_01_lastRecord != record) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                }

                if (record != 0 && __recordtilde_01_wIndex < loopEnd) {
                    for (number channel = 0; channel < 2; channel++) {
                        number effectiveChannel = channel + 0;

                        if (effectiveChannel < maxChannel) {
                            __recordtilde_01_buffer->setSample(channel, __recordtilde_01_wIndex, input[(Index)channel][(Index)i]);
                            touched = true;
                        } else
                            break;
                    }

                    __recordtilde_01_wIndex++;

                    if ((bool)(__recordtilde_01_loop) && __recordtilde_01_wIndex >= loopEnd) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                } else {
                    sync[(Index)i] = 0;
                }

                if ((bool)(!(bool)(__recordtilde_01_append)))
                    __recordtilde_01_lastRecord = record;
            }
        }

        if ((bool)(touched)) {
            __recordtilde_01_buffer->setTouched(true);
            __recordtilde_01_buffer->setSampleRate(this->sr);
        }
    }

    this->recordtilde_01_lastRecord = __recordtilde_01_lastRecord;
    this->recordtilde_01_wIndex = __recordtilde_01_wIndex;
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

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
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

void ip_05_perform(SampleValue * out, Index n) {
    auto __ip_05_lastValue = this->ip_05_lastValue;
    auto __ip_05_lastIndex = this->ip_05_lastIndex;

    for (Index i = 0; i < n; i++) {
        out[(Index)i] = ((SampleIndex)(i) >= __ip_05_lastIndex ? __ip_05_lastValue : this->ip_05_sigbuf[(Index)i]);
    }

    __ip_05_lastIndex = 0;
    this->ip_05_lastIndex = __ip_05_lastIndex;
}

void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void groove_01_perform(
    const Sample * rate_auto,
    const Sample * begin,
    const Sample * end,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(out2);
    RNBO_UNUSED(out1);
    auto __groove_01_crossfade = this->groove_01_crossfade;
    auto __groove_01_loop = this->groove_01_loop;
    auto __groove_01_playStatus = this->groove_01_playStatus;
    auto __groove_01_readIndex = this->groove_01_readIndex;
    auto __groove_01_jumpto = this->groove_01_jumpto;
    auto __groove_01_incomingChange = this->groove_01_incomingChange;
    auto __groove_01_changeIncomingInSamples = this->groove_01_changeIncomingInSamples;
    auto __groove_01_buffer = this->groove_01_buffer;
    SampleArray<2> out = {out1, out2};
    SampleIndex bufferLength = (SampleIndex)(__groove_01_buffer->getSize());
    Index i = 0;

    if (bufferLength > 1) {
        auto effectiveChannels = this->minimum(__groove_01_buffer->getChannels(), 2);
        number srMult = 0.001 * __groove_01_buffer->getSampleRate();
        number srInv = (number)1 / this->sr;
        number rateMult = __groove_01_buffer->getSampleRate() * srInv;

        for (; i < n; i++) {
            Index channel = 0;
            number offset = 0;
            number loopMin = begin[(Index)i] * srMult;
            loopMin = (loopMin > bufferLength - 1 ? bufferLength - 1 : (loopMin < 0 ? 0 : loopMin));
            number loopMax = (end[(Index)i] < 0 ? bufferLength : end[(Index)i] * srMult);
            loopMax = (loopMax > bufferLength ? bufferLength : (loopMax < 0 ? 0 : loopMax));

            if (loopMin >= loopMax) {
                offset = loopMax;
                loopMax = bufferLength;
                loopMin -= offset;
            }

            number loopLength = loopMax - loopMin;
            number currentRate = rate_auto[(Index)i] * rateMult;
            number currentSync = 0;

            if (__groove_01_changeIncomingInSamples > 0) {
                __groove_01_changeIncomingInSamples--;

                if (__groove_01_changeIncomingInSamples <= 0) {
                    if (__groove_01_incomingChange == 1) {
                        if (__groove_01_jumpto >= 0) {
                            __groove_01_readIndex = __groove_01_jumpto * srMult;

                            if (__groove_01_readIndex < loopMin)
                                __groove_01_readIndex = loopMin;
                            else if (__groove_01_readIndex >= loopMax)
                                __groove_01_readIndex = loopMax - 1;

                            __groove_01_jumpto = -1;
                        } else if (currentRate < 0) {
                            __groove_01_readIndex = loopMax - 1;
                        } else {
                            __groove_01_readIndex = loopMin;
                        }

                        __groove_01_playStatus = 1;
                    } else if (__groove_01_incomingChange == 0) {
                        __groove_01_playStatus = 0;
                    }

                    __groove_01_incomingChange = 2;
                }
            }

            if (loopLength > 0) {
                if (currentRate != 0) {
                    if (__groove_01_playStatus == 1) {
                        if ((bool)(__groove_01_loop)) {
                            while (__groove_01_readIndex < loopMin) {
                                __groove_01_readIndex += loopLength;
                            }

                            while (__groove_01_readIndex >= loopMax) {
                                __groove_01_readIndex -= loopLength;
                            }
                        } else if (__groove_01_readIndex >= loopMax || __groove_01_readIndex < loopMin) {
                            __groove_01_playStatus = 0;
                            break;
                        }

                        for (; channel < effectiveChannels; channel++) {
                            number outSample = (currentRate == 1 ? this->groove_01_getSample((Index)(channel), trunc(__groove_01_readIndex), offset, bufferLength) : this->groove_01_interpolatedSample(
                                (Index)(channel),
                                __groove_01_readIndex,
                                loopMax,
                                loopLength,
                                offset,
                                bufferLength
                            ));

                            if (__groove_01_crossfade > 0) {
                                out[(Index)channel][(Index)i] = this->groove_01_crossfadedSample(
                                    outSample,
                                    __groove_01_readIndex,
                                    (Index)(channel),
                                    currentRate,
                                    loopMin,
                                    loopMax,
                                    loopLength,
                                    offset,
                                    bufferLength
                                );
                            } else {
                                out[(Index)channel][(Index)i] = outSample;
                            }
                        }

                        {
                            currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                        }

                        __groove_01_readIndex += currentRate;
                    }
                } else {
                    if (__groove_01_playStatus == 1) {
                        currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                    }
                }
            }

            {
                sync[(Index)i] = currentSync;
            }

            for (; channel < 2; channel++) {
                if (__groove_01_playStatus <= 0)
                    sync[(Index)i] = 0;

                out[(Index)channel][(Index)i] = 0;
            }
        }
    }

    for (; i < n; i++) {
        if (__groove_01_playStatus <= 0)
            sync[(Index)i] = 0;

        for (number channel = 0; channel < 2; channel++) {
            out[(Index)channel][(Index)i] = 0;
        }
    }

    this->groove_01_changeIncomingInSamples = __groove_01_changeIncomingInSamples;
    this->groove_01_incomingChange = __groove_01_incomingChange;
    this->groove_01_jumpto = __groove_01_jumpto;
    this->groove_01_readIndex = __groove_01_readIndex;
    this->groove_01_playStatus = __groove_01_playStatus;
}

void trapezoid_tilde_01_perform(
    const Sample * phase,
    number rampUp,
    number rampDown,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(rampDown);
    RNBO_UNUSED(rampUp);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number __rampDown = 0.9;
        number __rampUp = 0.1;
        number __phase = phase[(Index)i];
        number tmp = 0.0;
        __phase = this->wrap(__phase, 0., 1.);
        __rampUp = (__rampUp > 1. ? 1. : (__rampUp < 0. ? 0. : __rampUp));
        __rampDown = (__rampDown > 1. ? 1. : (__rampDown < 0. ? 0. : __rampDown));

        if (__rampDown < __rampUp)
            __rampDown = __rampUp;

        if (__phase < __rampUp) {
            tmp = this->safediv(__phase, __rampUp);
        } else if (__phase > __rampDown) {
            tmp = 1. - this->safediv(__phase - __rampDown, 1. - __rampDown);
        } else {
            tmp = 1.;
        }

        out1[(Index)i] = tmp;
    }
}

void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * 3;//#map:_###_obj_###_:1
    }
}

void dspexpr_06_perform(const Sample * in1, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = rnbo_tanh(in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void selector_02_perform(
    const Sample * onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff[(Index)i] >= 1 && onoff[(Index)i] < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff[(Index)i] >= 2 && onoff[(Index)i] < 3)
            out[(Index)i] = in2[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void selector_01_perform(
    const Sample * onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff[(Index)i] >= 1 && onoff[(Index)i] < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff[(Index)i] >= 2 && onoff[(Index)i] < 3)
            out[(Index)i] = in2[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_01_srout_set(number ) {}

void data_01_chanout_set(number ) {}

void data_01_sizeout_set(number v) {
    this->data_01_sizeout = v;
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

void ip_02_dspsetup(bool force) {
    if ((bool)(this->ip_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->ip_02_lastIndex = 0;
    this->ip_02_setupDone = true;
}

number groove_01_getSample(
    Index channel,
    SampleIndex index,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    if (offset > 0) {
        index += offset;

        if (index >= bufferLength)
            index -= bufferLength;
    }

    return this->groove_01_buffer->getSample(channel, index);
}

number groove_01_interpolatedSample(
    Index channel,
    number index,
    SampleIndex end,
    SampleIndex length,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    SampleIndex index1 = (SampleIndex)(trunc(index));
    number i_x = index - index1;
    number i_1px = 1. + i_x;
    number i_1mx = 1. - i_x;
    number i_2mx = 2. - i_x;
    number i_a = i_1mx * i_2mx;
    number i_b = i_1px * i_x;
    number i_p1 = -.1666667 * i_a * i_x;
    number i_p2 = .5 * i_1px * i_a;
    number i_p3 = .5 * i_b * i_2mx;
    number i_p4 = -.1666667 * i_b * i_1mx;
    SampleIndex index2 = (SampleIndex)(index1 + 1);

    if (index2 >= end)
        index2 -= length;

    SampleIndex index3 = (SampleIndex)(index1 + 2);

    if (index3 >= end)
        index3 -= length;

    SampleIndex index4 = (SampleIndex)(index1 + 3);

    if (index4 >= end)
        index4 -= length;

    return this->groove_01_getSample(channel, index1, offset, bufferLength) * i_p1 + this->groove_01_getSample(channel, index2, offset, bufferLength) * i_p2 + this->groove_01_getSample(channel, index3, offset, bufferLength) * i_p3 + this->groove_01_getSample(channel, index4, offset, bufferLength) * i_p4;
}

number groove_01_crossfadedSample(
    SampleValue out,
    number readIndex,
    Index channel,
    number rate,
    number loopMin,
    number loopMax,
    number loopLength,
    number offset,
    number bufferLength
) {
    auto crossFadeStart1 = this->maximum(loopMin - this->groove_01_crossfadeInSamples, 0);
    auto crossFadeEnd1 = this->minimum(crossFadeStart1 + this->groove_01_crossfadeInSamples, bufferLength);
    number crossFadeStart2 = crossFadeStart1 + loopLength;
    auto crossFadeEnd2 = this->minimum(crossFadeEnd1 + loopLength, bufferLength);
    number crossFadeLength = crossFadeEnd2 - crossFadeStart2;

    if (crossFadeLength > 0) {
        crossFadeEnd1 = crossFadeStart1 + crossFadeLength;
        number diff = -1;
        number addFactor = 0;

        if (readIndex >= crossFadeStart2) {
            diff = readIndex - crossFadeStart2;
            addFactor = -1;
        } else if (readIndex < crossFadeEnd1) {
            diff = crossFadeEnd1 - readIndex + loopMax - crossFadeStart2;
            addFactor = 1;
        }

        if (diff >= 0) {
            number out2ReadIndex = readIndex + loopLength * addFactor;
            number out2 = (rate == 1 ? this->groove_01_getSample(channel, trunc(out2ReadIndex), offset, bufferLength) : this->groove_01_interpolatedSample(channel, out2ReadIndex, loopMax, loopLength, offset, bufferLength));
            number out2Factor = diff / crossFadeLength;
            number out1Factor = 1 - out2Factor;
            return out * out1Factor + out2 * out2Factor;
        }
    }

    return out;
}

number groove_01_calcSync(
    number readIndex,
    number offset,
    number loopMin,
    number loopLength,
    SampleIndex bufferLength,
    number srInv
) {
    RNBO_UNUSED(srInv);
    RNBO_UNUSED(bufferLength);
    RNBO_UNUSED(offset);

    {
        {
            return (readIndex - loopMin) / loopLength;
        }
    }
}

void groove_01_dspsetup(bool force) {
    if ((bool)(this->groove_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->groove_01_crossfadeInSamples = this->mstosamps(this->groove_01_crossfade);
    this->groove_01_setupDone = true;
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

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void data_01_init() {
    this->data_01_buffer->setWantsFill(true);
}

Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_01_dspsetup(bool force) {
    if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
        return;

    {
        if (this->data_01_sizemode == 2) {
            this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
            updateDataRef(this, this->data_01_buffer);
        } else if (this->data_01_sizemode == 3) {
            this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->sr, this->vs));
            updateDataRef(this, this->data_01_buffer);
        }
    }

    this->data_01_setupDone = true;
}

void data_01_afterBufferUpdate() {
    this->data_01_report();
}

void data_01_report() {
    {
        this->data_01_srout_set(this->data_01_buffer->getSampleRate());
        this->data_01_chanout_set(this->data_01_buffer->getChannels());
    }

    this->data_01_sizeout_set(this->data_01_buffer->getSize());
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

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
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
    dspexpr_01_in2 = 1;
    ip_01_value = 0;
    ip_01_impulse = 0;
    selector_01_onoff = 1;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    selector_02_onoff = 1;
    select_01_test1 = 1;
    recordtilde_01_append = 0;
    recordtilde_01_record = 0;
    recordtilde_01_begin = 0;
    recordtilde_01_end = -1;
    recordtilde_01_loop = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 1;
    ip_02_value = 1;
    ip_02_impulse = 0;
    groove_01_rate_auto = 1;
    groove_01_jumpto = -1;
    groove_01_begin = 0;
    groove_01_end = -1;
    groove_01_loop = 1;
    groove_01_crossfade = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    ip_03_value = 0;
    ip_03_impulse = 0;
    param_01_value = 1;
    param_02_value = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 3;
    trapezoid_tilde_01_phase = 0;
    trapezoid_tilde_01_rampUp = 0.1;
    trapezoid_tilde_01_rampDown = 0.9;
    dspexpr_06_in1 = 0;
    ip_04_value = 0;
    ip_04_impulse = 0;
    param_03_value = 0;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    data_01_sizeout = 0;
    data_01_size = 0;
    data_01_sizems = 2000;
    data_01_normalize = 0.995;
    data_01_channels = 2;
    ip_05_value = 0;
    ip_05_impulse = 0;
    param_04_value = 100;
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
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    ip_01_lastIndex = 0;
    ip_01_lastValue = 0;
    ip_01_resetCount = 0;
    ip_01_sigbuf = nullptr;
    ip_01_setupDone = false;
    recordtilde_01_wIndex = 0;
    recordtilde_01_lastRecord = 0;
    ip_02_lastIndex = 0;
    ip_02_lastValue = 0;
    ip_02_resetCount = 0;
    ip_02_sigbuf = nullptr;
    ip_02_setupDone = false;
    groove_01_readIndex = 0;
    groove_01_playStatus = 0;
    groove_01_changeIncomingInSamples = 0;
    groove_01_incomingChange = 2;
    groove_01_crossfadeInSamples = 0;
    groove_01_setupDone = false;
    ip_03_lastIndex = 0;
    ip_03_lastValue = 0;
    ip_03_resetCount = 0;
    ip_03_sigbuf = nullptr;
    ip_03_setupDone = false;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    ip_04_lastIndex = 0;
    ip_04_lastValue = 0;
    ip_04_resetCount = 0;
    ip_04_sigbuf = nullptr;
    ip_04_setupDone = false;
    param_03_lastValue = 0;
    data_01_sizemode = 2;
    data_01_setupDone = false;
    ip_05_lastIndex = 0;
    ip_05_lastValue = 0;
    ip_05_resetCount = 0;
    ip_05_sigbuf = nullptr;
    ip_05_setupDone = false;
    param_04_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "grained";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number ip_01_value;
    number ip_01_impulse;
    number selector_01_onoff;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number selector_02_onoff;
    number select_01_test1;
    number recordtilde_01_append;
    number recordtilde_01_record;
    number recordtilde_01_begin;
    number recordtilde_01_end;
    number recordtilde_01_loop;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number ip_02_value;
    number ip_02_impulse;
    number groove_01_rate_auto;
    number groove_01_jumpto;
    number groove_01_begin;
    number groove_01_end;
    number groove_01_loop;
    number groove_01_crossfade;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number ip_03_value;
    number ip_03_impulse;
    number param_01_value;
    number param_02_value;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number trapezoid_tilde_01_phase;
    number trapezoid_tilde_01_rampUp;
    number trapezoid_tilde_01_rampDown;
    number dspexpr_06_in1;
    number ip_04_value;
    number ip_04_impulse;
    number param_03_value;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number ip_05_value;
    number ip_05_impulse;
    number param_04_value;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[7];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    SampleIndex ip_01_lastIndex;
    number ip_01_lastValue;
    SampleIndex ip_01_resetCount;
    signal ip_01_sigbuf;
    bool ip_01_setupDone;
    Float32BufferRef recordtilde_01_buffer;
    SampleIndex recordtilde_01_wIndex;
    number recordtilde_01_lastRecord;
    SampleIndex ip_02_lastIndex;
    number ip_02_lastValue;
    SampleIndex ip_02_resetCount;
    signal ip_02_sigbuf;
    bool ip_02_setupDone;
    Float32BufferRef groove_01_buffer;
    number groove_01_readIndex;
    Index groove_01_playStatus;
    SampleIndex groove_01_changeIncomingInSamples;
    Int groove_01_incomingChange;
    SampleIndex groove_01_crossfadeInSamples;
    bool groove_01_setupDone;
    SampleIndex ip_03_lastIndex;
    number ip_03_lastValue;
    SampleIndex ip_03_resetCount;
    signal ip_03_sigbuf;
    bool ip_03_setupDone;
    number param_01_lastValue;
    number param_02_lastValue;
    SampleIndex ip_04_lastIndex;
    number ip_04_lastValue;
    SampleIndex ip_04_resetCount;
    signal ip_04_sigbuf;
    bool ip_04_setupDone;
    number param_03_lastValue;
    Float32BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    SampleIndex ip_05_lastIndex;
    number ip_05_lastValue;
    SampleIndex ip_05_resetCount;
    signal ip_05_sigbuf;
    bool ip_05_setupDone;
    number param_04_lastValue;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef grained;
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

