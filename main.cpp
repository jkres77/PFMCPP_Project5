/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 you can safely ignore any warnings about exit-time-destructors.
 if you would like to suppress them, add -Wno-exit-time-destructors to the .replit file 
   with the other warning suppression flags
 */




#include <iostream>
/*
 copied UDT 1:
 */
struct ChannelStrip
{
    int numKnobs;
    int numFaders;
    float maxGainRange;
    float labelTextSize;
    int numInputs;

    ChannelStrip();
    ~ChannelStrip();

    void func()
    {
        std::cout << "Number of channels: " << this->addChannel(4) << " Number of inputs: " << this->numInputs << std::endl;
    }

    void makeAdjustments(float volume, float panning, bool mute);
    void acceptMicInput(bool isConnected);
    void acceptAudioInput(bool isConnected, bool isMono);
    float addChannel(int numChannels);
};

ChannelStrip::ChannelStrip()
{
    numKnobs = 4;
    numFaders = 1;
    maxGainRange = 12.0f;
    labelTextSize = 2.4f;
    numInputs = 2;
}

ChannelStrip::~ChannelStrip()
{
    std::cout << "Removing Channel Strip" << std::endl;
}

void ChannelStrip::makeAdjustments(float volume, float panning, bool mute)
{
    maxGainRange = 8.0f;
    volume = 7.3f;
    panning = -1.2f;
    mute = false;
}

void ChannelStrip::acceptMicInput(bool isConnected)
{
    if (numInputs == 3)
    {
        isConnected = true;
    }
}

void ChannelStrip::acceptAudioInput(bool isConnected, bool isMono)
{
    acceptMicInput(false);
    isConnected = true;
    isMono = false;
    std::cout << "How loud can it go? " << maxGainRange << "db" << std::endl;
}

float ChannelStrip::addChannel(int numChannels)
{
    int channel = 1;

    for (int i = 0; i < numChannels; i++)
    {
        ++channel;
        std::cout << "adding channel num: " << channel << std::endl;
    }
    return channel;
}
/*
 copied UDT 2:
 */
struct Equalizer
{
    int numBands;
    double maxFreqRange;
    std::string knobColor;
    std::string filterType;
    double knobSmoothness;

    Equalizer();
    ~Equalizer();

    void func()
    {
        std::cout << "Number of bands: " << this->addBand() << " Max Freq Range: " << this->maxFreqRange << std::endl;
    }

    double boostBass(float level, float freqRange);
    double cutHiFreq(float amountToCut, float freqRange);
    double adjustWidth(double level);
    int addBand();
};

Equalizer::Equalizer()
{
    numBands = 3;
    maxFreqRange = 20000.0;
    knobColor = "Blue";
    filterType = "lowShelf";
    knobSmoothness = 2.6;
}

Equalizer::~Equalizer()
{
    std::cout << "Turning EQ off" << std::endl; 
}

double Equalizer::boostBass(float level, float freqRange)
{
    level = 24.0f;
    freqRange = 94.0f;

    return 0;
}

double Equalizer::cutHiFreq(float amountToCut, float freqRange)
{
    if (amountToCut > freqRange)
    {
        freqRange = 1200.0f;
    }

    return static_cast<double>(freqRange);
}

double Equalizer::adjustWidth(double level)
{
    if (level > 12.0)
    {
        level = 12.0;
    } 

    return level;
}

int Equalizer::addBand()
{
    while(numBands < 8)
    {  
        numBands += 1;        
    }
    return numBands;
}
/*
 copied UDT 3:
 */
struct Preamp
{
    float quality;
    int numControls;
    float gainIncrease;
    double lineSensitivity;
    bool clippingIndicator;

    Preamp();
    ~Preamp();

    void func()
    {
        std::cout << "How much mid reduction: " << this->cutMud(12.0f) << " Gain increase: " <<  this->gainIncrease << std::endl;
    }

    float boostAmp(float level);
    float trimAmp(float level);
    float distortSignal(float level, bool allowClip = false);
    float cutMud(float level);
};

Preamp::Preamp()
{
    quality = 96.0f;
    numControls = 1;
    gainIncrease = 24.0f;
    lineSensitivity = 10.0;
    clippingIndicator = false;
}

Preamp::~Preamp()
{
    std::cout << "Shutting down preamp" << std::endl;
}

float Preamp::boostAmp(float level)
{
    level *= gainIncrease;

    return level;
}

float Preamp::trimAmp(float level)
{
    level = gainIncrease - 5.0f;

    return level;
}

float Preamp::distortSignal(float level, bool allowClip)
{
    if (!allowClip)
    {
        if (gainIncrease > 24.0f)
        {
            level = 12.0f;
        }
    }
    else 
    {
        level = gainIncrease;
    }

    return level;
}

float Preamp::cutMud(float level)
{
    Equalizer eq;
    while (eq.numBands >= 2 && level >= 4)
    {
        level -= 3.0f;  
    }
    return level;
}

/*
 new UDT 4:
 with 2 member functions
 */

struct Mixer
{
    ChannelStrip channel1, channel2;
    Equalizer eq;

    Mixer();
    ~Mixer();

    float setChannels(int numChannels, bool isMono);
    void applyEq(bool activate, int numBands);

};

Mixer::Mixer()
{
    channel1.acceptAudioInput(false, true);
    channel2.acceptAudioInput(false, true);
    eq.numBands = 1;
}

Mixer::~Mixer()
{
    std::cout << "Clear channels" << std::endl;
    channel1.numInputs = 0;
    std::cout << "Channel 1 clear" << std::endl;
    channel2.numInputs = 0;
    std::cout << "Channel 2 clear" << std::endl;
}

/*
 new UDT 5:
 with 2 member functions
 */
struct FxModule
{
    Equalizer hpf, lpf;
    Preamp distortion;

    FxModule();
    ~FxModule();

    void setFrequency(float lpf, float hpf);
    void processDistortion(bool activate, float level);
};

FxModule::FxModule()
{
    hpf.maxFreqRange = 1000.0;
    lpf.maxFreqRange = 20000.0;
    distortion.distortSignal(0.0f, false);
}

FxModule::~FxModule()
{
    std::cout << "Deactivate FX Module" << std::endl;
    distortion.distortSignal(0.0f, false);
    hpf.filterType = "none";
    lpf.filterType = "none";
    std::cout << "FX Module is off" << std::endl;
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>
int main()
{
    // Example::main();
    // return 0;
    
    ChannelStrip channel;
    channel.acceptAudioInput(true, false);
    channel.makeAdjustments(7.4f, 0.0f, false);

    std::cout << "Should I turn it down? " << (channel.numInputs == 1 ? "No" : "Yes") << "\n";

    std::cout << "Number of channels: " << channel.addChannel(4) << " Number of inputs: " << channel.numInputs << std::endl;

    channel.func();

    //=========================================================

    Equalizer eq;

    std::cout << "Number of bands: " << eq.addBand() << " Max Freq Range: " << eq.maxFreqRange << std::endl;

    eq.func();

    //=========================================================

    Preamp pre;

    std::cout << "How much mid reduction: " << pre.cutMud(12.0f) << " Gain increase: " << pre.gainIncrease << std::endl;

    pre.func();

    //========================================================

    Mixer mixer;

    //========================================================

    FxModule fx;
    
    std::cout << "good to go!" << std::endl;
}
