// Datastructures.cc

#include "datastructures.hh"

#include <random>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here

}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here

}

int Datastructures::calculate_brightness(const Color& color) const
{
    return 3 * color.r + 6 * color.g + color.b;
}

bool Datastructures::add_beacon(BeaconID id, const Name& name, Coord xy, Color color)
{
    if (beacons_.find(id) != beacons_.end()) {
        return false;
    }

    Beacon new_beacon;
    new_beacon.name = name;
    new_beacon.xy = xy;
    new_beacon.color = color;

    beacons_[id] = new_beacon;

    return true;
}

int Datastructures::beacon_count()
{
    return beacons_.size();
}

void Datastructures::clear_beacons()
{
    beacons_.clear();
}

std::vector<BeaconID> Datastructures::all_beacons()
{
    vector<BeaconID> keys; // keys are beacon ids

    for (auto it = beacons_.begin(); it != beacons_.end(); ++it) {
        keys.push_back(it->first);
    }

    return keys;
}

Name Datastructures::get_name(BeaconID id)
{
    auto it = beacons_.find(id);

    if (it != beacons_.end()) {
        return it->second.name;
    }

    return NO_NAME;
}

Coord Datastructures::get_coordinates(BeaconID id)
{
    auto it = beacons_.find(id);

    if (it != beacons_.end()) {
        return it->second.xy;
    }

    return NO_COORD;
}

Color Datastructures::get_color(BeaconID id)
{
    auto it = beacons_.find(id);

    if (it != beacons_.end()) {
        return it->second.color;
    }

    return NO_COLOR;
}

std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    std::vector<BeaconID> result = all_beacons();

    // Sort by beacon name alphabetically
    std::sort(result.begin(), result.end(),
        [this](const BeaconID& a, const BeaconID& b) {
            return beacons_[a].name < beacons_[b].name;
        });

    return result;
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    std::vector<BeaconID> result = all_beacons();

    // Sort by beacon brightness
    std::sort(result.begin(), result.end(),
        [this](const BeaconID& a, const BeaconID& b) {
            int brightness_a = calculate_brightness(beacons_[a].color);
            int brightness_b = calculate_brightness(beacons_[b].color);
            return brightness_a < brightness_b;
    });

    return result;
}

BeaconID Datastructures::min_brightness()
{
    if (beacons_.empty()) {
        return NO_BEACON;
    }

    auto it = beacons_.begin();
    BeaconID min_id = it->first;
    int min_brightness = calculate_brightness(it->second.color);

    ++it; // start from the second element
    for (; it != beacons_.end(); ++it) {
        BeaconID id = it->first;
        int brightness = calculate_brightness(it->second.color);

        if (min_brightness > brightness) {
            min_brightness = brightness;
            min_id = id;
        }
    }

    return min_id;
}

BeaconID Datastructures::max_brightness()
{
    if (beacons_.empty()) {
        return NO_BEACON;
    }

    auto it = beacons_.begin();
    BeaconID max_id = it->first;
    int max_brightness = calculate_brightness(it->second.color);

    ++it;
    for(; it != beacons_.end(); ++it) {
        BeaconID id = it->first;
        int brightness = calculate_brightness(it->second.color);

        if (max_brightness < brightness) {
            max_brightness = brightness;
            max_id = id;
        }
    }

    return max_id;
}

std::vector<BeaconID> Datastructures::find_beacons(Name const& /*name*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::change_beacon_name(BeaconID /*id*/, const Name& /*newname*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_lightbeam(BeaconID /*sourceid*/, BeaconID /*targetid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

Color Datastructures::total_color(BeaconID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::add_fibre(Coord /*xpoint1*/, Coord /*xpoint2*/, Cost /*cost*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<Coord> Datastructures::all_xpoints()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<Coord, Cost> > Datastructures::get_fibres_from(Coord /*xpoint*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<Coord, Coord> > Datastructures::all_fibres()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_fibre(Coord /*xpoint1*/, Coord /*xpoint2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

void Datastructures::clear_fibres()
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<Coord, Cost> > Datastructures::route_any(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_least_xpoints(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_fastest(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

std::vector<Coord> Datastructures::route_fibre_cycle(Coord /*startxpoint*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}
