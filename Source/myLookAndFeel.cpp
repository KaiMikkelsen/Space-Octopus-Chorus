//
//  myLookAndFeel.cpp
//  KaiKhorus
//
//  Created by Kai Mikkelsen on 2021-12-20.
//

/*
  ==============================================================================

    Created: 14 Dec 2017 10:16:04am
    Author:  Stefan Remberg

  ==============================================================================
*/

#include "myLookAndFeel.h"

//==============================================================================
myLookAndFeel::myLookAndFeel()
{
    //juce::File knobImageFile1 = juce::File::getSpecialLocation
    //(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("purple3.png");
    //(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("bluey.png");
    
    img1 = juce::ImageCache::getFromMemory(BinaryData::bluey_png, BinaryData::bluey_pngSize);
    
    //juce::ImageCache::getFromMemory(BinaryData::LEDOff_png, BinaryData::LEDOff_pngSize);
    
    //(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("darkgreen.png");
    //img1 = juce::ImageCache::getFromFile(knobImageFile1);
}

//==============================================================================
void myLookAndFeel::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height, float sliderPos,
                                       float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{

    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = fmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        juce::Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(juce::Colours::white);

        g.drawFittedText(juce::String("No Image"), text_bounds.getSmallestIntegerContainer(),
            juce::Justification::horizontallyCentred | juce::Justification::centred, 1);
    }
}

void myLookAndFeel::drawButtonText (juce::Graphics& g, juce::TextButton& button,
                                     bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/)
{
    //juce::Font font (getTextButtonFont (button, button.getHeight()));
    //juce::Font font = (juce::Font (juce::Typeface::createSystemTypefaceFor (BinaryData::Micra_Normal_ttf, BinaryData::Micra_Normal_ttfSize)));
    
    juce::Font font = (juce::Font (juce::Typeface::createSystemTypefaceFor (BinaryData::AstroSpaceeZ2Bg_ttf, BinaryData::AstroSpaceeZ2Bg_ttfSize)));
    font.setHeight(24.0f);
    g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                                            : juce::TextButton::textColourOffId)
                       .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = fmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = fmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = juce::roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = fmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = fmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          juce::Justification::centred, 2);
}


/*
//==============================================================================
myLookAndFeelV2::myLookAndFeelV2()
{
}

//==============================================================================
void myLookAndFeelV2::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin(width / 2, height / 2) *0.85f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    float fwidth = (float)width;
    float fheight = (float)height;
    const float angle = rotaryStartAngle
        + sliderPos
        * (rotaryEndAngle - rotaryStartAngle);

    g.setColour(Colour(0xff39587a));
    Path filledArc;
    filledArc.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, rotaryEndAngle, 0.6);

    g.fillPath(filledArc);

    g.setColour(Colours::lightgreen);
    Path filledArc1;
    filledArc1.addPieSegment(rx, ry, rw + 1, rw + 1, rotaryStartAngle, angle, 0.6);

    g.fillPath(filledArc1);

    Path p;
    const float pointerLength = radius * 0.63f;
    const float pointerThickness = radius * 0.2f;
    p.addRectangle(-pointerThickness * 0.5f, -radius - 1, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(Colour(0xff39587a));
    g.fillPath(p);

    const float dotradius = radius * (float)0.4;
    const float dotradius2 = rw * (float)0.4;
    g.setColour(Colour(0xff39587a));
    g.fillEllipse(centreX - (dotradius),
        centreY - (dotradius),
        dotradius2, dotradius2);
}

//==============================================================================
myLookAndFeelV3::myLookAndFeelV3()
{
    File knobImageFile2 = File::getSpecialLocation
    (File::SpecialLocationType::userDesktopDirectory).getChildFile("knob2.png");
    img2 = ImageCache::getFromFile(knobImageFile2);
}

//==============================================================================
void myLookAndFeelV3::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    if (img2.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img2.getHeight() / img2.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img2,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img2.getWidth(),
            img2.getWidth(),
            img2.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}

*/