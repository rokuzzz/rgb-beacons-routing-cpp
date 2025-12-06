// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <algorithm>

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
    std::vector<BeaconID> keys; // keys are beacon ids

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

std::vector<BeaconID> Datastructures::find_beacons(Name const& name)
{
    std::vector<BeaconID> result;

    for(auto it = beacons_.begin(); it != beacons_.end(); ++it) {
        BeaconID id = it->first;
        Beacon& beacon = it->second;

        if (beacon.name == name) {
            result.push_back(id);
        }
    }

    return result;
}

bool Datastructures::change_beacon_name(BeaconID id, const Name& newname)
{
    auto it = beacons_.find(id);
    if (it != beacons_.end()) {
        it->second.name = newname;
        return true;
    }

    return false;
}

bool Datastructures::add_lightbeam(BeaconID sourceid, BeaconID targetid)
{
    auto source_it = beacons_.find(sourceid);
    if (source_it == beacons_.end()) {
        return false;  // source not found
    }

    auto target_it = beacons_.find(targetid);
    if (target_it == beacons_.end()) {
        return false;  // target not found
    }

    if (source_it->second.target != NO_BEACON) {
        return false;  // source beacon is already sending light to another beacon
    }

    source_it->second.target = targetid;
    target_it->second.sources.insert(sourceid);

    return true;
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id)
{
    auto it = beacons_.find(id);

    // Check if beacon exists
    if (it == beacons_.end()) {
        return {};  // Return empty vector
    }

    // Convert set to vector (already sorted)
    std::vector<BeaconID> result(it->second.sources.begin(), it->second.sources.end());

    return result;
}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id)
{
    std::vector<BeaconID> result;

    // Check if starting beacon exists
    auto it = beacons_.find(id);
    if (it == beacons_.end()) {
        return {NO_BEACON};
    }

    BeaconID current = id;

    // Add starting beacon
    result.push_back(current);

    // Follow the path
    while (beacons_[current].target != NO_BEACON) {
        current = beacons_[current].target;  // move to target
        result.push_back(current);           // add to result
    }

    return result;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented();
}

Color Datastructures::total_color(BeaconID id)
{
    auto it = beacons_.find(id);
    if (it == beacons_.end()) {
        return NO_COLOR;
    }

    Beacon& beacon = it->second;

    int sum_r = beacon.color.r;
    int sum_g = beacon.color.g;
    int sum_b = beacon.color.b;
    int count = 1;

    for (const BeaconID& source_id : beacon.sources) {
        Color source_total = total_color(source_id);

        sum_r += source_total.r;
        sum_g += source_total.g;
        sum_b += source_total.b;
        count += 1;
    }

    int total_r = sum_r/count;
    int total_g = sum_g/count;
    int total_b = sum_b/count;

    return Color{total_r, total_g, total_b};
}

bool Datastructures::add_fibre(Coord xpoint1, Coord xpoint2, Cost cost)
{
    // Check if points are the same
    if (xpoint1 == xpoint2) {
        return false;
    }

    // Check if connection already exists
    if (fiber_network_[xpoint1].count(xpoint2)) {
        return false;
    }

    // Add fiber in BOTH directions
    fiber_network_[xpoint1][xpoint2] = cost;
    fiber_network_[xpoint2][xpoint1] = cost;

    return true;
}

std::vector<Coord> Datastructures::all_xpoints()
{
    std::set<Coord> points_set;
    for(const auto& [coord, cost] : fiber_network_) {
        points_set.insert(coord);
    }

    return std::vector<Coord>(points_set.begin(), points_set.end());
}

std::vector<std::pair<Coord, Cost> > Datastructures::get_fibres_from(Coord xpoint)
{
    if(fiber_network_.find(xpoint) == fiber_network_.end()) {
        return {};
    }

    std::vector<std::pair<Coord, Cost>> result;
    for (const auto& [coord, cost] : fiber_network_[xpoint]) {
        result.push_back({coord, cost});
    }

    return result;
}

std::vector<std::pair<Coord, Coord>> Datastructures::all_fibres()
{
    std::vector<std::pair<Coord, Coord>> result;

    // Collect all fibers, avoiding duplicates by only including pairs where coord1 < coord2
    for (const auto& [coord1, neighbours] : fiber_network_) {
        for (const auto& [coord2, cost] : neighbours) {
            if (coord1 < coord2) {
                result.push_back({coord1, coord2});
            }
        }
    }

    // Sort automatically using Coord's operator "<" (compares Y first, then X)
    std::sort(result.begin(), result.end());
    return result;
}

bool Datastructures::remove_fibre(Coord xpoint1, Coord xpoint2)
{
    if(fiber_network_[xpoint1].count(xpoint2) == 0) {
        return false;
    }

    fiber_network_[xpoint1].erase(xpoint2);
    fiber_network_[xpoint2].erase(xpoint1);

    return true;
}

void Datastructures::clear_fibres()
{
    fiber_network_.clear();
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
