import subprocess
import unittest
import os

class TestNQueensSolvers(unittest.TestCase):
    # Binary paths - adjust these if your names in the build/ directory differ
    SOLVERS = {
        "naive": "./build/queens_naive",
        "bitmask": "./build/queens_bitmask",
        "cuda": "./build/queens_cuda"
    }

    # Official results for the N-Queens problem (OEIS A000170)
    EXPECTED_RESULTS = {
        1: 1,
        4: 2,
        5: 10,
        6: 4,
        8: 92,
        10: 724,
        12: 14200
    }

    def run_solver(self, solver_path, n):
        """Runs the solver process and parses the output in N,Sols,Time format."""
        if not os.path.exists(solver_path):
            self.skipTest(f"Solver {solver_path} not found. Ensure it is compiled!")
            
        try:
            # Run the binary with N as an argument
            result = subprocess.run([solver_path, str(n)], capture_output=True, text=True, timeout=30)
            if result.returncode != 0:
                return None
            
            # Parse CSV formatted output: n,solutions,time
            output = result.stdout.strip().split(',')
            return int(output[1]) # Return the solution count
        except Exception as e:
            print(f"Error executing {solver_path}: {e}")
            return None

    def test_all_solvers(self):
        """Tests every available solver against the set of known N values."""
        for n, expected in self.EXPECTED_RESULTS.items():
            for name, path in self.SOLVERS.items():
                with self.subTest(solver=name, n=n):
                    actual = self.run_solver(path, n)
                    self.assertEqual(actual, expected, 
                        f"Solver '{name}' failed for N={n}. Expected {expected}, got {actual}")

if __name__ == "__main__":
    unittest.main()