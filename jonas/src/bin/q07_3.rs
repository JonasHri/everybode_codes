extern crate itertools;
use itertools::Itertools;
use std::fs;

fn unwrap_track(
    track: &Vec<Vec<char>>,
    i_last: i32,
    j_last: i32,
    i_cur: i32,
    j_cur: i32,
) -> String {
    let offsets = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];

    for offset in offsets {
        let i_next = i_cur + offset.0;
        let j_next = j_cur + offset.1;
        if i_next < 0 || i_next >= (track.len() as i32) {
            continue;
        }
        if j_next < 0 || j_next >= (track[0].len() as i32) {
            continue;
        }
        if i_next == i_last && j_next == j_last {
            continue;
        }
        match track[i_next as usize][j_next as usize] {
            'S' => return "".to_string(),
            '+' | '-' | '=' => {
                return track[i_next as usize][j_next as usize].to_string()
                    + &unwrap_track(track, i_cur, j_cur, i_next, j_next)
            }
            _ => continue,
        }
    }
    println!("you fucked up");
    "".to_string()
}

fn main() {
    let track_data: Vec<Vec<char>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q07_p3_track.txt")
            .unwrap()
            .lines()
            .map(|line| line.chars().collect())
            .collect();

    let track_str = "S".to_owned() + &unwrap_track(&track_data, 1, 0, 0, 0);
    let track: Vec<char> = track_str.chars().collect();
    println!("track: {}", track_str);
    let data: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q07_p3.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    let steps = track.len() * 2024;
    let mut results: Vec<(&str, i64)> = vec![];
    for chariot in &data {
        let name_plan = chariot.split(":").collect::<Vec<&str>>();
        let name = name_plan[0];
        let plan = name_plan[1];
        let changes = plan.split(",").collect::<Vec<&str>>();
        let mut cur_power = 10;
        let mut collected_power: i64 = 0;
        for i in 0..steps {
            cur_power += match track[(i + 1) % track.len()] {
                '+' => 1,
                '-' => -1,
                _ => match changes[i % changes.len()] {
                    "+" => 1,
                    "-" => -1,
                    _ => 0,
                },
            };
            collected_power += cur_power;
        }
        results.push((name, collected_power));
    }
    results.sort_by_key(|x| -x.1);

    let to_beat = results[0].1;
    println!("{}", to_beat);

    let mut winners = 0;
    let start_plan = vec!["+", "+", "+", "+", "+", "-", "-", "-", "=", "=", "="];

    for changes in start_plan.iter().permutations(start_plan.len()).unique() {
        let mut cur_power = 10;
        let mut collected_power: i64 = 0;
        for i in 0..steps {
            cur_power += match track[(i + 1) % track.len()] {
                '+' => 1,
                '-' => -1,
                _ => match changes[i % changes.len()] {
                    &"+" => 1,
                    &"-" => -1,
                    _ => 0,
                },
            };
            collected_power += cur_power;
        }

        if collected_power > to_beat {
            winners += 1;
        }
    }

    println!("winners: {}", winners);
}
