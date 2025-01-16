use std::fs;

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

fn find_powers(field: &Vec<Vec<char>>) -> Vec<(usize, usize, usize)> {
    let mut indexes = Vec::new();

    for (i, row) in field.iter().enumerate() {
        for (j, &value) in row.iter().enumerate() {
            match value {
                'H' => indexes.push((i, j, 2)),
                'T' => indexes.push((i, j, 1)),
                _ => (),
            }
        }
    }

    indexes
}
fn main() {
    let field: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q12_p2.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    field.iter().for_each(|x| println!("{:?}", x));

    let targets = find_powers(&field);

    let catapults = vec!['C', 'B', 'A'];
    let cata_locs: Vec<(usize, usize)> = catapults
        .iter()
        .map(|x| find_indexes(&field, *x)[0])
        .collect();

    println!("{:?}", targets);
    println!("{:?}", cata_locs);
    let mut score = 0;
    for target in targets {
        for cata_loc in &cata_locs {
            let j_target = target.1 - target.0 + cata_loc.0;
            if (j_target - cata_loc.1) % 3 == 0 {
                score += (20 - cata_loc.0) * ((j_target - cata_loc.1) / 3) * target.2;
                break;
            }
        }
    }

    println!("{}", score);
}
