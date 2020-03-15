import java.util.Comparator;
import java.util.Arrays;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;

public class p630 {
    // Course Schedule III - hard

    // There are n different online courses numbered from 1 to n. Each course has
    // some duration(course length) t and closed on dth day. A course should be
    // taken continuously for t days and must be finished before or on the dth day.
    // You will start at the 1st day.

    // Given n online courses represented by pairs (t,d), your task is to find the
    // maximal number of courses that can be taken.

    public static void main(String[] args) {
        runTest(new int[] { 100, 200, 200, 1300, 1000, 1250, 2000, 3200 }, 3);
        runTest(new int[] { 5, 15, 3, 19, 6, 7, 2, 10, 5, 16, 8, 14, 10, 11, 2, 19 }, 5);
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
            // String spacer = getSpacer(course);
            // System.out.println(spacer + "considering timeFree: " + timeFree + ", course: " + course);

            if (course == courses.length) {
                // System.out.println(spacer + "base result: " + 0);
                // return reportResult(0, spacer, timeFree, course);
                return 0;
            }

            if (memo.get(course).containsKey(timeFree)) {
                int cached = memo.get(course).get(timeFree);
                // System.out.println(spacer + "cached result: " + cached);
                // return reportResult(cached, spacer, timeFree, course);
                return cached;
            }

            // calculate result of not taking this course
            int result = recursively(timeFree, course + 1, courses, memo);

            // consider taking this course if I can
            int[] next = courses[course];
            if (timeFree + next[0] <= next[1]) {
                int usingCourse = recursively(timeFree + next[0], course + 1, courses, memo) + 1;
                result = Math.max(usingCourse, result);
            }

            memo.get(course).put(timeFree, result);
            // return reportResult(result, spacer, timeFree, course);
            return result;

        }

        int reportResult(int result, String spacer, int timeFree, int course) {
            System.out.println(spacer + "result of timeFree: " + timeFree + ", course: " + course + ": " + result);
            return result;
        }
        
        String getSpacer(int n) {
            char[] sc = new char[n];
            Arrays.fill(sc, '\t');
            return new String(sc);
        }

        class CourseComparator implements Comparator<int[]> {
            @Override
            public int compare(int[] a, int[] b) {
                // if equally urgent, prefer courses that are shorter
                if (a[1] == b[1])
                    return a[0] - b[0];
                return a[1] - b[1];
            }
        }
    }
}