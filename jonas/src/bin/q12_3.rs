use std::cmp;
use std::fs;
use std::usize;

use itertools::Itertools;

fn main() {
    let meteors: Vec<(usize, usize)> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q12_p3.txt")
            .unwrap()
            .lines()
            .map(|line| {
                line.split(" ")
                    .map(|y| y.parse::<usize>().unwrap())
                    .collect_tuple()
                    .unwrap()
            })
            .collect();

    let max_width = meteors.iter().map(|x| x.0).max().unwrap() as usize;
    let max_height = meteors.iter().map(|x| x.1).max().unwrap() as usize;
    // width, height, power mult
    let catas = vec![(0, 0, 1), (0, 1, 2), (0, 2, 3)];

    let mut cata_times: Vec<Vec<Vec<usize>>> = Vec::new();
    let mut cata_scores: Vec<Vec<Vec<usize>>> = Vec::new();

    for cat in catas {
        let mut cata_time = vec![vec![0; max_height]; max_width];
        let mut cata_score = vec![vec![usize::max_value(); max_height]; max_width];
        for power in 0..max_height / 2 {
            let mut proj_pos = cat.clone();
            let mut time = 0;
            for _ in 0..power {
                if proj_pos.0 >= max_width - 1 {
                    break;
                }
                proj_pos.0 += 1;
                proj_pos.1 += 1;
                time += 1;
                cata_time[proj_pos.0][proj_pos.1] = time;
                cata_score[proj_pos.0][proj_pos.1] =
                    cmp::min(cata_score[proj_pos.0][proj_pos.1], cat.2 * power);
            }
            for _ in 0..power {
                if proj_pos.0 >= max_width - 1 {
                    break;
                }
                proj_pos.0 += 1;
                // proj_pos.1+=1;
                time += 1;
                cata_time[proj_pos.0][proj_pos.1] = time;
                cata_score[proj_pos.0][proj_pos.1] =
                    cmp::min(cata_score[proj_pos.0][proj_pos.1], cat.2 * power);
            }
            for _ in 0..cmp::max(power, proj_pos.1) {
                if proj_pos.0 >= max_width - 1 {
                    break;
                }
                proj_pos.0 += 1;
                proj_pos.1 -= 1;
                time += 1;
                cata_time[proj_pos.0][proj_pos.1] = time;
                cata_score[proj_pos.0][proj_pos.1] =
                    cmp::min(cata_score[proj_pos.0][proj_pos.1], cat.2 * power);
            }
        }
        cata_times.push(cata_time);
        cata_scores.push(cata_score);
    }

    for j in (0..20).rev() {
        for i in 0..40 {
            if cata_scores[0][i][j] != usize::max_value() {
                print!("{} ", cata_times[0][i][j]);
            } else {
                print!("  ");
            }
        }
        println!();
    }

    let mut score: usize = 0;

    for meteor in meteors {
        let mut max_alt = 0;
        let mut min_score = usize::max_value();
        for i in 0..cata_times.len() {
            let mut met_pos = meteor.clone();
            let times = &cata_times[i];
            let scores = &cata_scores[i];

            for timestamp in 1..cmp::min(meteor.0, meteor.1) {
                met_pos.0 -= 1;
                met_pos.1 -= 1;
                if times[met_pos.0][met_pos.1] == 0 {
                    continue;
                }
                if times[met_pos.0][met_pos.1] > timestamp {
                    continue;
                }

                if met_pos.1 < max_alt {
                    continue;
                }
                if scores[met_pos.0][met_pos.1] > min_score && met_pos.1 == max_alt {
                    continue;
                }
                max_alt = met_pos.1;
                min_score = scores[met_pos.0][met_pos.1];
            }
        }
        score += min_score;
    }

    println!("{}", score);
}
