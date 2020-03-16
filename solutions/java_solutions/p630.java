import java.util.Comparator;
import java.util.Arrays;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

public class p630 {
    // Course Schedule III - Hard

    // There are n different online courses numbered from 1 to n. Each course has
    // some duration(course length) t and closed on dth day. A course should be
    // taken continuously for t days and must be finished before or on the dth day.
    // You will start at the 1st day.

    // Given n online courses represented by pairs (t,d), your task is to find the
    // maximal number of courses that can be taken.

    public static void main(String[] args) {
        runTest(new int[] { 100, 200, 200, 1300, 1000, 1250, 2000, 3200 }, 3);
        runTest(new int[] { 5, 15, 3, 19, 6, 7, 2, 10, 5, 16, 8, 14, 10, 11, 2, 19 }, 5);
        runTest(new int[] { 100, 2, 32, 50 }, 1);
        runTest(new int[] { 7, 17, 3, 12, 10, 20, 9, 10, 5, 20, 10, 19, 4, 18 }, 4);
        runTest(new int[] { 9, 20, 4, 14, 4, 10, 6, 7, 2, 14, 8, 10, 6, 6, 5, 7 }, 4);
    }

    static void runTest(int[] data, int expected) {
        int[][] courses = parseTestData(data);
        Solution s = new Solution();
        int actual = s.scheduleCourse(courses);
        if (actual != expected) {
            printTestFailure(courses, expected, actual);
        }
    }

    static int[][] parseTestData(int[] data) {
        int[][] courses = new int[data.length / 2][2];
        for (int i = 0; i < data.length - 1; i += 2) {
            courses[i / 2][0] = data[i];
            courses[i / 2][1] = data[i + 1];
        }
        return courses;
    }

    static void printTestFailure(int[][] courses, int expected, int actual) {
        String[] courseStrings = new String[courses.length];
        for (int i = 0; i < courses.length; i++)
            courseStrings[i] = Arrays.toString(courses[i]);
        String totalCourses = Arrays.toString(courseStrings);

        System.out.println(
                "Unexpected result for courses: " + totalCourses + ", exptected: " + expected + ", but got: " + actual);
    }

    static class Solution {
        public int scheduleCourse(int[][] courses) {
            return iteratively(courses);
        }

        int iteratively(int[][] courses) {
            Arrays.sort(courses, new CourseComparator());
            PriorityQueue<Integer> q = new PriorityQueue<>(new CourseLengthComparator(courses));
            int timeFree = 0;
            int count = 0;
            for (int i = 0; i < courses.length; i++) {
                q.add(i);
                // greedily take on courses as available
                if (timeFree + courses[i][0] <= courses[i][1]) {
                    timeFree += courses[i][0];
                    count++;
                } else {
                    // if I can't take this course, mark the most restrictive course as not taken
                    int max_i = q.poll();
                    // if i am keeping this course and dropping the other course
                    if (courses[max_i][0] > courses[i][0])
                        timeFree += courses[i][0] - courses[max_i][0];
                    courses[max_i][0] = -1;
                }
            }
            return count;
        }

        // simple memo table runs out of memory on test 67
        int withSimpleMemoTable(int[][] courses) {
            Arrays.sort(courses, new CourseComparator());
            // lots of unused slots if ending times have large gaps!
            int latestEnding = courses[courses.length - 1][1];
            Integer[][] memo = new Integer[courses.length][latestEnding + 1];
            return recursively(0, 0, courses, memo);
        }

        int recursively(int timeFree, int course, int[][] courses, Integer[][] memo) {
            if (course == courses.length)
                return 0;
            if (memo[course][timeFree] != null)
                return memo[course][timeFree];

            int with = 0;
            if (timeFree + courses[course][0] <= courses[course][1]) {
                with = recursively(timeFree + courses[course][0], course + 1, courses, memo) + 1;
            }
            int without = recursively(timeFree, course + 1, courses, memo);

            return memo[course][timeFree] = Math.max(with, without);
        }

        // complex memo table runs out of time on test 67
        int withComplexMemoTable(int[][] courses) {
            Arrays.sort(courses, new CourseComparator());
            List<HashMap<Integer, Integer>> memo = generateMemoTable(courses.length);
            return recursively(0, 0, courses, memo);
        }

        List<HashMap<Integer, Integer>> generateMemoTable(int numCourses) {
            List<HashMap<Integer, Integer>> memo = new ArrayList<>(numCourses);
            for (int i = 0; i < numCourses; i++) {
                memo.add(new HashMap<>());
            }
            return memo;
        }

        int recursively(int timeFree, int course, int[][] courses, List<HashMap<Integer, Integer>> memo) {
            if (course == courses.length)
                return 0;

            if (memo.get(course).containsKey(timeFree))
                return memo.get(course).get(timeFree);

            // calculate result of not taking this course
            int result = recursively(timeFree, course + 1, courses, memo);

            // consider taking this course if I can
            int[] next = courses[course];
            if (timeFree + next[0] <= next[1]) {
                int usingCourse = recursively(timeFree + next[0], course + 1, courses, memo) + 1;
                result = Math.max(usingCourse, result);
            }

            memo.get(course).put(timeFree, result);
            return memo.get(course).put(timeFree, result);
        }

        class CourseComparator implements Comparator<int[]> {
            @Override
            public int compare(int[] a, int[] b) {
                return a[1] - b[1];
            }
        }

        class CourseLengthComparator implements Comparator<Integer> {
            int[][] courses;

            CourseLengthComparator(int[][] courses) {
                this.courses = courses;
            }

            @Override
            public int compare(Integer a, Integer b) {
                return courses[b][0] - courses[a][0];
            }
        }
    }
}