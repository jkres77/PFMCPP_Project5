/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

 Destructors
        
 0) move all of your implementations of all functions to OUTSIDE of the class. 
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

 3) add 2 new UDTs that use only the types you copied above as member variables.

 4) add 2 member functions that use your member variables to each of these new UDTs

 5) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 6) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 7) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
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
    ChannelStrip channel;
    channel.acceptAudioInput(true, false);
    channel.makeAdjustments(7.4f, 0.0f, false);

    std::cout << "Should I turn it down? " << (channel.numInputs == 1 ? "No" : "Yes") << "\n";

    auto chanCount = channel.addChannel(4);

    std::cout << "Number of channels: " << chanCount << std::endl;

    //=========================================================

    Equalizer eq;

    auto bands = eq.addBand();

    std::cout << "Number of bands: " << bands << std::endl;

    //=========================================================

    Preamp pre;

    auto cut = pre.cutMud(10.0f);

    std::cout << "How much mid reduction: " << cut << std::endl;

    //========================================================

    Mixer mixer;

    //========================================================

    FxModule fx;
    
    std::cout << "good to go!" << std::endl;
}
