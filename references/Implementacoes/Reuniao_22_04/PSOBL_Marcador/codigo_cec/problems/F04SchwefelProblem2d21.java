/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package clonalg_metamodel.problems;

import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F04SchwefelProblem2d21 extends Problem {

    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    private double[] boundBase = {-100, 100};

    public F04SchwefelProblem2d21(Configuration configuration, int dimension) {
        this.configuration = configuration;
        this.dimension = dimension;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
        double[] x = null;
        if (gene instanceof double[]) {
            x = (double[]) gene;
        } else {
            int[] variableSize = new int[getNumberOfVariables()];
            for (int i = 0; i < variableSize.length; i++) {
                variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
            }
            x = configuration.getUtilitaries().getRealFromBinary((boolean[])gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
        }
        double[] result = new double[1];
	result[0] = -1;
	double var;
        for (int i = 0; i < dimension; i++) {
	    var = Math.abs(x[i]);
	    result[0] = var > result[0]? var: result[0];
        }
        return result;
    }

    @Override
    public double[][] getBounds() {
        if (bound==null) {
            bound = new double[dimension][2];
            for (int i = 0; i < bound.length; i++) {
                bound[i][0] = boundBase[0];
                bound[i][1] = boundBase[1];
            }
        }
        return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
        //return 500000;
	//return 50000;
	return 40000; //usado no paper EI2010
    }

    @Override
    public double getBestValue() {
	//return 0.3; //FEP
	//return 9.44;
	return 0.00005325212; //icaris2010
    }

    @Override
    public Problem clone() {
	return new F04SchwefelProblem2d21(configuration, dimension);
    }

}
