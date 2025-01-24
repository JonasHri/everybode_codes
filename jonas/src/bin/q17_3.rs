use std::{fs, usize};

fn find_indexes(field: &Vec<Vec<char>>, target: char) -> Vec<(usize, usize)> {
    let mut indexes = Vec::new();

    for (i, row) in field.iter().enumerate() {
        for (j, &value) in row.iter().enumerate() {
            if value == target {
                indexes.push((i, j));
            }
        }
    }

    indexes
}

fn main() {
    let sky: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q17_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let star_cords = find_indexes(&sky, '*');

    let mut in_cluster = vec![false; star_cords.len()];

    let mut distances: Vec<(usize, usize, usize)> = Vec::new();

    for i in 0..star_cords.len() {
        for j in 0..star_cords.len() {
            if i == j {
                continue;
            }
            let dist = star_cords[i].0.abs_diff(star_cords[j].0)
                + star_cords[i].1.abs_diff(star_cords[j].1);
            distances.push((i, j, dist));
            distances.push((j, i, dist));
        }
    }

    distances.sort_by(|a, b| a.2.cmp(&b.2));

    let mut brill_lengths: Vec<usize> = Vec::new();

    for &(s1_start, s2_start, dist_start) in &distances {
        if dist_start >= 6 {
            break;
        }
        if in_cluster[s1_start] || in_cluster[s2_start] {
            continue;
        }

        let mut total_length = dist_start;
        let mut star_count = 2;
        in_cluster[s1_start] = true;
        in_cluster[s2_start] = true;

        let mut cluster_growth = true;

        while cluster_growth {
            cluster_growth = false;
            for &(s1, s2, dist) in &distances {
                if in_cluster[s1] && !in_cluster[s2] && dist < 6 {
                    in_cluster[s2] = true;
                    total_length += dist;
                    star_count += 1;
                    cluster_growth = true;
                    break;
                }
            }
        }
        brill_lengths.push(total_length + star_count);
    }

    brill_lengths.sort();

    let last = brill_lengths.len() - 1;

    println!(
        "{}",
        brill_lengths[last] * brill_lengths[last - 1] * brill_lengths[last - 2]
    );
}
