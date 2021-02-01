/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via 'this->' and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
        d) you should see 2 (almost) identical messages in the program output for each member function you add:
            one for the std::cout line, and one for the member function's output
 
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}

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
    Example::main();
    return 0;
    
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
